using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using MapEditor.GameObject;

namespace SplitTools
{
    public partial class FrmMapEditor : Form
    {
        Panel _pnlMap;
        Bitmap _currentImage;

        int _imgHeight;
        int _imgWidth;

        int _tileHeight;
        int _tileWidth;

        //Ma tran tile
        int[][] _matrix;

        int _col;
        int _row;

        string[] _arrPathName;

        ArrayList _listTile;
        Image _imgGameObj;
        List<GameObj> _listGameObj;
        
        int _idGameObj;
        TypeObj _Type;

        BufferedGraphicsContext grpContext;
        BufferedGraphics bufGrp;
        bool _IsMouseDown = false;

        public FrmMapEditor()
        {
            InitializeComponent();
            _listTile = new ArrayList();
            _listGameObj = new List<GameObj>();
            _idGameObj = 0;
        }
        private void Innit()
        {
            this._imgHeight = this._currentImage.Height;
            this._imgWidth = this._currentImage.Width;

            //Khoi tao 
            _pnlMap = new Panel
            {
                Height = this._currentImage.Height,
                Width = this._currentImage.Width
            };
            _pnlMap.Paint += _pnlMap_Paint;
            _pnlMap.MouseMove += _pnlMap_MouseMove;
            _pnlMap.MouseDown += _pnlMap_MouseDown;
            _pnlMap.MouseUp += _pnlMap_MouseUp;
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
                    WriteGameObj(saveDlg.FileName);
                    MessageBox.Show("Done");
                }
            }
        }
        private void TsBtnClear_Click(object sender, EventArgs e)
        {
            _currentImage = null;
            pnlView.Controls.Remove(_pnlMap);
            _matrix = null;
            _listGameObj = new List<GameObj>();
            _imgGameObj = null;
            _idGameObj = 0;
            tsbtnSave.Enabled = false;
            tsbtnCreateMap.Enabled = true;
        }
        private void FrmMapEditor_Load(object sender, EventArgs e)
        {
            _pnlMap = new Panel();
            tsbtnSave.Enabled = false;
        }

        #region Graphics

        private void DrawGrid()
        {
            bufGrp.Graphics.DrawImage(_currentImage, _pnlMap.DisplayRectangle);
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
        private void DrawGameObjects()
        {
            if (_listGameObj.Count != 0)
            {
                bufGrp.Graphics.DrawImage(_currentImage, this._pnlMap.DisplayRectangle);
                for (int i = 0; i < _listGameObj.Count; i++)
                {
                    bufGrp.Graphics.DrawImage(_listGameObj[i].Image, _listGameObj[i].bounds);
                }
                bufGrp.Render();
            }
        }
        private void DrawMap()
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

            if (_listGameObj.Count != 0)
            {
                for (int i = 0; i < _listGameObj.Count; i++)
                {
                    bufGrp.Graphics.DrawImage(_listGameObj[i].Image, _listGameObj[i].bounds);
                }
            }

            bufGrp.Render();
        }
        private void HScrollBar_ValueChanged(object sender, EventArgs e)
        {
            _pnlMap.Left = -this.hScrollBar.Value;
            DrawMap();
        }
        private void VScrollBar_ValueChanged(object sender, EventArgs e)
        {
            _pnlMap.Top = -this.vScrollBar.Value;
            DrawMap();
        }
        private void _pnlMap_Paint(object sender, PaintEventArgs e)
        {
            DrawGrid();
        }
        private void _pnlMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (_imgGameObj != null)
            {
                Rectangle Rect = new Rectangle(e.X - _imgGameObj.Width / 2, e.Y - _imgGameObj.Height / 2, _imgGameObj.Width, _imgGameObj.Height);
                FormatBound(ref Rect);

                if (_IsMouseDown == true)
                {
                    int temID = _idGameObj;
                    GameObj Obj = new GameObj(temID, Rect, _Type, _imgGameObj);

                    if (Colision(_listGameObj, Obj))
                    {
                        _listGameObj.Add(Obj);
                        _idGameObj++;
                    }
                }

                DrawMap();
                bufGrp.Graphics.DrawImage(_imgGameObj, Rect);
                bufGrp.Render();
            }
        }
        private void _pnlMap_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                _imgGameObj = null;
                _IsMouseDown = false;
                return;
            }
            if (e.Button == MouseButtons.Left)
            {
                if (_imgGameObj != null)
                {
                    _IsMouseDown = true;

                    Rectangle Rect = new Rectangle(e.X - _imgGameObj.Width / 2, e.Y - _imgGameObj.Height / 2, _imgGameObj.Width, _imgGameObj.Height);
                    FormatBound(ref Rect);
                    if (_IsMouseDown == true)
                    {
                        int temID = _idGameObj;
                        GameObj Obj = new GameObj(temID, Rect, _Type, _imgGameObj);

                        if (Colision(_listGameObj, Obj))
                        {
                            _listGameObj.Add(Obj);
                            _idGameObj++;
                        }
                    }
                }
            }

        }
        private void _pnlMap_MouseUp(object sender, MouseEventArgs e)
        {
            _IsMouseDown = false;
        }
        bool Colision(List<GameObj> list, GameObj obj)
        {
            if (list.Count == 0)
                return true;
            else
            {
                for (int i = 0; i < list.Count; i++)
                {
                    if (Rectangle.Intersect(list[i].bounds, obj.bounds).Height > 2 && Rectangle.Intersect(list[i].bounds, obj.bounds).Width > 2)
                        return false;
                }
                return true;
            }
        }
        void FormatBound(ref Rectangle rect)
        {
            int AlignFactor = 1;

            if (RdbAlign16.Checked)
                AlignFactor = 16;

            if (RdbAlignNone.Checked)
                AlignFactor = 1;

            //rect X
            int dLeftOut = rect.X - ((int)rect.X / AlignFactor) * AlignFactor;
            int dleftIn = (((int)rect.X / AlignFactor) + 1) * AlignFactor - rect.X;
            int dRightIn = rect.X + rect.Width - ((int)(rect.X + rect.Width) / AlignFactor) * AlignFactor;
            int dRightOut = ((int)(rect.X + rect.Width) / AlignFactor + 1) * AlignFactor - (rect.X + rect.Width);
            //find min X
            int minLeft = (dleftIn < dLeftOut) ? dleftIn : dLeftOut;
            int minRight = (dRightIn < dRightOut) ? dRightIn : dRightOut;
            int minX = (minLeft < minRight) ? minLeft : minRight;

            if (minX == dLeftOut || minX == dRightIn)
            {
                rect.X -= minX;
            }
            else
            {
                rect.X += minX;
            }

            //rect Y
            int dTopOut = rect.Y - ((int)rect.Y / AlignFactor) * AlignFactor;
            int dTopIn = (((int)rect.Y / AlignFactor) + 1) * AlignFactor - rect.Y;
            int dBottomIn = rect.Y + rect.Width - ((int)(rect.Y + rect.Width) / AlignFactor) * AlignFactor;
            int dBottomOut = ((int)(rect.Y + rect.Width) / AlignFactor + 1) * AlignFactor - (rect.Y + rect.Width);
            //find min
            int minTop = (dTopIn < dTopOut) ? dTopIn : dTopOut;
            int minBottom = (dBottomIn < dBottomOut) ? dBottomIn : dBottomOut;
            int minY = (minTop < minBottom) ? minTop : minBottom;

            if (minY == dTopOut || minY == dBottomIn)
            {
                rect.Y -= minY;
            }
            else
                rect.Y += minY;
        }
        #endregion

        #region Title map
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
        }

        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int memcmp(IntPtr b1, IntPtr b2, long count);
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
        private void WriteFileMap(string filePath)
        {
            FileStream fs;
            fs = new FileStream(filePath, FileMode.Create);
            using (StreamWriter sWriter = new StreamWriter(fs, Encoding.UTF8))
            {
                int imgOfRow = (int)Math.Ceiling((double)(_imgWidth / _tileWidth));
                int imgOfCol = (int)Math.Ceiling((double)(_listTile.Count / imgOfRow));
                if (imgOfCol == 0) imgOfCol = 1;

                sWriter.WriteLine(imgOfRow + " " + imgOfCol);
                sWriter.WriteLine(_col + " " + _row);
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

        #region Game Object
        private void WriteGameObj(string FilePath)
        {
            FileStream fs = new FileStream(String.Format("{0}{1}", FilePath.Substring(0, FilePath.Length - 4), "-GameObj.txt"), FileMode.Create);
            using (StreamWriter sWriter = new StreamWriter(fs, Encoding.UTF8))
            {
                int size = _listGameObj.Count;
                for (int i = 0; i < size; i++)
                {
                    sWriter.WriteLine(_listGameObj[i].Id.ToString() + "\t" + (int)_listGameObj[i].Type + "\t" + _listGameObj[i].bounds.X.ToString() + "\t" + _listGameObj[i].bounds.Y.ToString() + "\t" + _listGameObj[i].bounds.Width.ToString() + "\t" + _listGameObj[i].bounds.Height);
                }
                sWriter.Close();
            }
            fs.Close();
        }
        #endregion
        private void PhiTieuObj_Click(object sender, EventArgs e)
        {
            _imgGameObj = PhiTieuObj.Image;
            _Type = TypeObj.PhiTieuObj;
        }

        private void BtnUndo_Click(object sender, EventArgs e)
        {
            if (_listGameObj.Count == 0)
                return;
            else
            {
                _listGameObj.RemoveAt(_listGameObj.Count - 1);
                bufGrp.Graphics.DrawImage(_currentImage, this._pnlMap.DisplayRectangle);
                DrawMap();
                bufGrp.Render();
            }
        }

    }
}
