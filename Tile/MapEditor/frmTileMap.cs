using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Drawing2D;


namespace SplitTools
{
    public partial class FrmMapEditor : Form
    {
        //Tao ra mot panel de chua anh
        Panel _pnlMap;

        //Giu buc anh hien tai
        Bitmap _currentImage;

        //Lay chieu dai va chieu rong cua buc anh
        int _imgHeight;
        int _imgWidth;

        //Lay chieu dai va rong cua tile
        int _tileHeight;
        int _tileWidth;

        //Tao ma tran luu lai vi tri cua cac tile
        int[][] _matrix;

        //Lay so dong va cot cua ma tran
        int _col;
        int _row;

        //Luu tat ca cac buc anh
        string[] _arrPathName;

        //Tao list de luu cac buc anh duoc cat ra
        ArrayList _listTile;
        //buffer
        BufferedGraphicsContext grpContext;
        BufferedGraphics bufGrp;

        #region Form Event
        public FrmMapEditor()
        {
            InitializeComponent();
            _listTile = new ArrayList();
        }
        private void Innit()
        {
            this._imgHeight = this._currentImage.Height;
            this._imgWidth = this._currentImage.Width;

            //Khoi tao 
            _pnlMap = new Panel();
            _pnlMap.Height = this._currentImage.Height;
            _pnlMap.Width = this._currentImage.Width;
            _pnlMap.Paint += _pnlMap_Paint;
            this.pnlView.Controls.Add(_pnlMap);

            //Khoi tao thanh cuon
            this.vScrollBar.Maximum = this._imgHeight + this._pnlMap.ClientSize.Height;
            this.hScrollBar.Maximum = this._imgWidth + this._pnlMap.ClientSize.Width;

            //Khoi tao ma tran
            this._row = this._imgHeight / this._tileHeight;
            this._col = this._imgWidth / this._tileHeight;
            this._matrix = new int[_row][];
            for (int i = 0; i < _row; i++)
            {
                this._matrix[i] = new int[_col];
            }

            grpContext = BufferedGraphicsManager.Current;
            bufGrp = grpContext.Allocate(this._pnlMap.CreateGraphics(), this._pnlMap.DisplayRectangle);
        }
        private void TsbtnCreateMap_Click(object sender, EventArgs e)
        {
            frmCreateMap frm = new frmCreateMap();
            frm.ShowDialog();
            if (!frm.Result())
            {
                if (frm.GetPathName() != null)
                {
                    _arrPathName = frm.GetPathName();
                    
                    Bitmap tempBM = new Bitmap(frm.GetFileName());
                    _currentImage = new Bitmap(tempBM, tempBM.Width, tempBM.Height);
                    _tileHeight = frm.GetTileHeiht();
                    _tileWidth = frm.GetTileWidth();
                    this.Innit();
                    tsbtnSave.Enabled = true;
                    tsbtnCreateMap.Enabled = false;
                }
            }
        }
        private void TsbtnSave_Click(object sender, EventArgs e)
        {

            SaveFileDialog saveDlg = new SaveFileDialog
            {
                Filter = "txt file|*.txt|All|*.*"
            };
            if (saveDlg.ShowDialog() == DialogResult.OK)
            {
                if (saveDlg.CheckPathExists)
                {
                    CreateMap(saveDlg.FileName);
                    WriteListTile(saveDlg.FileName);
                }
            }
        }
        private void TsBtnClear_Click(object sender, EventArgs e)
        {
            _currentImage = null;
            pnlView.Controls.Remove(_pnlMap);
            _matrix = null;
            tsbtnSave.Enabled = false;
            tsbtnCreateMap.Enabled = true;
        }
        private void FrmMapEditor_Load(object sender, EventArgs e)
        {
            _pnlMap = new Panel();
            tsbtnSave.Enabled = false;
        }
        #endregion

        #region Xu ly giao dien
        private void HScrollBar_ValueChanged(object sender, EventArgs e)
        {
            this._pnlMap.Left = -this.hScrollBar.Value;
        }

        private void VScrollBar_ValueChanged(object sender, EventArgs e)
        {
            this._pnlMap.Top = -this.vScrollBar.Value;
        }

        private void _pnlMap_Paint(object sender, PaintEventArgs e)
        {
            bufGrp.Graphics.DrawImage(_currentImage, this._pnlMap.DisplayRectangle);
            Pen pen = new Pen(Color.White);
            for (int i = 1; i < _col; i++)
            {
                bufGrp.Graphics.DrawLine(pen, i * _tileWidth, 0, i * _tileWidth, _imgHeight);
            }
            for (int j = 1; j < _row; j++)
            {
                bufGrp.Graphics.DrawLine(pen, 0, j * _tileHeight, _imgWidth, j * _tileHeight);
            }
            bufGrp.Render();
        }

        #endregion

        #region Xu ly tile map
        private void CloneImage()
        {
            Bitmap cloneBitmap;
            PixelFormat formatImg = this._currentImage.PixelFormat;
            for (int i = 0; i < _row; i++)
            {
                for (int j = 0; j < _col; j++)
                {
                    cloneBitmap = this._currentImage.Clone(new Rectangle(j * this._tileHeight, i * this._tileWidth, this._tileWidth, this._tileHeight), formatImg);
                    this._matrix[i][j] = AddImageToListTile(cloneBitmap);
                }
            }
            MessageBox.Show("Successfully");
        }

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int memcmp(IntPtr b1, IntPtr b2, long count);

        //Them tile vao list
        public int AddImageToListTile(Bitmap bitCloneImg)
        {
            if (this._listTile.Count == 0)
            {
                this._listTile.Add(bitCloneImg);
                //return this._listTile.Count - 1;
                return this._listTile.Count;
            }
            Bitmap imgItem;
            for (int i = 0; i < this._listTile.Count; i++)
            {
                imgItem = this._listTile[i] as Bitmap;
                if (CompareMemCmp(imgItem, bitCloneImg))
                {
                    //return i;
                    return i + 1;
                }
            }
            _listTile.Add(bitCloneImg);
            //return _listTile.Count - 1;
            return _listTile.Count;
        }

        //so sanh hai anh bitmap
        public bool CompareMemCmp(Bitmap b1, Bitmap b2)
        {
            if ((b1 == null) != (b2 == null)) return false;
            if (b1.Size != b2.Size) return false;

            var bd1 = b1.LockBits(new Rectangle(new Point(0, 0), b1.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            var bd2 = b2.LockBits(new Rectangle(new Point(0, 0), b2.Size), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);

            try
            {
                IntPtr bd1scan0 = bd1.Scan0;
                IntPtr bd2scan0 = bd2.Scan0;

                int stride = bd1.Stride;
                int len = stride * b1.Height;

                return memcmp(bd1scan0, bd2scan0, len) == 0;
            }
            finally
            {
                b1.UnlockBits(bd1);
                b2.UnlockBits(bd2);
            }
        }
        private Bitmap MergeImage()
        {
            //So buc anh tren mot dong
            //int imgOfRow = (int)Math.Sqrt(2 * this._listTile.Count);
            int imgOfRow = (int)Math.Ceiling((double)(_imgWidth / _tileWidth));
            //So buc anh tren mot cot
            //int imgOfCol = (int)(this._listTile.Count / imgOfRow) + 1; // ???
            int imgOfCol = (int)Math.Ceiling((double)(_listTile.Count / imgOfRow));
            if (imgOfCol == 0) imgOfCol = 1;

            Bitmap imgResult = new Bitmap(imgOfRow * this._tileWidth, imgOfCol * this._tileHeight);
            using (Graphics grp = Graphics.FromImage(imgResult))
            {
                Bitmap imgItem;
                for (int i = 0; i < this._listTile.Count; i++)
                {
                    imgItem = this._listTile[i] as Bitmap;
                    grp.DrawImage(imgItem, new Rectangle((i % imgOfRow) * this._tileWidth, (i / imgOfRow) * this._tileHeight, this._tileWidth, this._tileHeight));
                }
            }
            return imgResult;
        }
        private void WriteListTile(string filePath)
        {
            MergeImage().Save(filePath.Substring(0, filePath.Length - 3) + "PNG");
        }
        #endregion

        #region Write tile map
        private void WriteFileMap(string filePath)
        {
            FileStream fs;
            fs = new FileStream(filePath, FileMode.Create);
            using (StreamWriter sWriter = new StreamWriter(fs, Encoding.UTF8))
            {
                sWriter.WriteLine(_row + " " + _col);
                sWriter.WriteLine(_tileHeight + " " + _tileWidth);

                for (int i = 0; i < _row; i++)
                {
                    for (int j = 0; j < _col; j++)
                    {
                        sWriter.Write(_matrix[i][j] + " ");
                    }
                    sWriter.WriteLine();
                }
            }
            fs.Close();
        }
        private void CreateMap(string FilePath)
        {
            foreach (string pathName in _arrPathName)
            {
                _currentImage = new Bitmap(pathName);
                Innit();

                if (this._currentImage != null)
                {
                    CloneImage();
                    WriteFileMap(String.Format("{0}{1}", FilePath.Substring(0, FilePath.Length - 4), "-MAP.txt"));
                }
                else
                {
                    MessageBox.Show("Image not found");
                }
            }
        }
        #endregion
    }
}
