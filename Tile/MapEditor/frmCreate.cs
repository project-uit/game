using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Resources;

namespace SplitTools
{
    public partial class frmCreateMap : Form
    {
        string[] FileName=null;
        string file =null;
        bool IsCancel = false;
        public frmCreateMap()
        {
            InitializeComponent();
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            OpenFileDialog opendlg = new OpenFileDialog();
            opendlg.Multiselect = true;
            opendlg.Filter = "(PNG file)|*.png|(All file)|*.*";
            opendlg.DefaultExt = "*.png";
            if (opendlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                if (opendlg.CheckFileExists)
                {
                    txtSource.Text = opendlg.FileName;
                    FileName = opendlg.FileNames;
                    file = opendlg.FileName;       
                }
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            IsCancel = true;
            this.Close();
        }

        public String[] GetPathName()
        {
            return FileName;            
        }
        public string GetFileName()
        {
                return file;
        }
        public int GetTileHeiht()
        {
            return int.Parse(txtTileHeight.Text);
        }
        public int GetTileWidth()
        {
            return int.Parse(txtTileWidth.Text);
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            IsCancel = false;
            this.Close();
        }
        public bool Result()
        {
            return IsCancel;
        }
    }
}
