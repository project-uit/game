namespace SplitTools
{
    partial class FrmMapEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmMapEditor));
            this.vScrollBar = new System.Windows.Forms.VScrollBar();
            this.hScrollBar = new System.Windows.Forms.HScrollBar();
            this.pnlView = new System.Windows.Forms.Panel();
            this.picbo = new System.Windows.Forms.PictureBox();
            this.tsbtnCreateMap = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbtnSave = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.BtnUndo = new System.Windows.Forms.ToolStripButton();
            this.tsBtnClear = new System.Windows.Forms.ToolStripButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.PhiTieuObj = new System.Windows.Forms.PictureBox();
            this.RdbAlign16 = new System.Windows.Forms.RadioButton();
            this.RdbAlignNone = new System.Windows.Forms.RadioButton();
            this.pnlView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picbo)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.PhiTieuObj)).BeginInit();
            this.SuspendLayout();
            // 
            // vScrollBar
            // 
            this.vScrollBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.vScrollBar.Location = new System.Drawing.Point(1874, 0);
            this.vScrollBar.Name = "vScrollBar";
            this.vScrollBar.Size = new System.Drawing.Size(17, 556);
            this.vScrollBar.TabIndex = 0;
            this.vScrollBar.ValueChanged += new System.EventHandler(this.VScrollBar_ValueChanged);
            // 
            // hScrollBar
            // 
            this.hScrollBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.hScrollBar.Location = new System.Drawing.Point(0, 556);
            this.hScrollBar.Name = "hScrollBar";
            this.hScrollBar.Size = new System.Drawing.Size(1874, 17);
            this.hScrollBar.TabIndex = 1;
            this.hScrollBar.ValueChanged += new System.EventHandler(this.HScrollBar_ValueChanged);
            // 
            // pnlView
            // 
            this.pnlView.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlView.Controls.Add(this.picbo);
            this.pnlView.Controls.Add(this.hScrollBar);
            this.pnlView.Controls.Add(this.vScrollBar);
            this.pnlView.Location = new System.Drawing.Point(0, 258);
            this.pnlView.Margin = new System.Windows.Forms.Padding(6);
            this.pnlView.Name = "pnlView";
            this.pnlView.Size = new System.Drawing.Size(1910, 596);
            this.pnlView.TabIndex = 3;
            // 
            // picbo
            // 
            this.picbo.Location = new System.Drawing.Point(330, -265);
            this.picbo.Margin = new System.Windows.Forms.Padding(4);
            this.picbo.Name = "picbo";
            this.picbo.Size = new System.Drawing.Size(128, 15);
            this.picbo.TabIndex = 14;
            this.picbo.TabStop = false;
            // 
            // tsbtnCreateMap
            // 
            this.tsbtnCreateMap.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbtnCreateMap.Name = "tsbtnCreateMap";
            this.tsbtnCreateMap.Size = new System.Drawing.Size(143, 36);
            this.tsbtnCreateMap.Text = "Create Map";
            this.tsbtnCreateMap.Click += new System.EventHandler(this.TsbtnCreateMap_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 39);
            // 
            // tsbtnSave
            // 
            this.tsbtnSave.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbtnSave.Name = "tsbtnSave";
            this.tsbtnSave.Size = new System.Drawing.Size(69, 36);
            this.tsbtnSave.Text = "Save";
            this.tsbtnSave.Click += new System.EventHandler(this.TsbtnSave_Click);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 39);
            // 
            // toolStrip1
            // 
            this.toolStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbtnCreateMap,
            this.toolStripSeparator1,
            this.tsbtnSave,
            this.toolStripSeparator2,
            this.BtnUndo,
            this.tsBtnClear});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Padding = new System.Windows.Forms.Padding(0, 0, 4, 0);
            this.toolStrip1.Size = new System.Drawing.Size(1910, 39);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // BtnUndo
            // 
            this.BtnUndo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.BtnUndo.Image = ((System.Drawing.Image)(resources.GetObject("BtnUndo.Image")));
            this.BtnUndo.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.BtnUndo.Name = "BtnUndo";
            this.BtnUndo.Size = new System.Drawing.Size(77, 36);
            this.BtnUndo.Text = "Undo";
            this.BtnUndo.Click += new System.EventHandler(this.BtnUndo_Click);
            // 
            // tsBtnClear
            // 
            this.tsBtnClear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tsBtnClear.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsBtnClear.Name = "tsBtnClear";
            this.tsBtnClear.Size = new System.Drawing.Size(73, 36);
            this.tsBtnClear.Text = "Clear";
            this.tsBtnClear.Click += new System.EventHandler(this.TsBtnClear_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.PhiTieuObj);
            this.groupBox1.Location = new System.Drawing.Point(0, 54);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(6);
            this.groupBox1.Size = new System.Drawing.Size(1730, 192);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Object";
            // 
            // PhiTieuObj
            // 
            this.PhiTieuObj.Image = ((System.Drawing.Image)(resources.GetObject("PhiTieuObj.Image")));
            this.PhiTieuObj.Location = new System.Drawing.Point(24, 37);
            this.PhiTieuObj.Margin = new System.Windows.Forms.Padding(6);
            this.PhiTieuObj.Name = "PhiTieuObj";
            this.PhiTieuObj.Size = new System.Drawing.Size(32, 31);
            this.PhiTieuObj.TabIndex = 0;
            this.PhiTieuObj.TabStop = false;
            this.PhiTieuObj.Click += new System.EventHandler(this.PhiTieuObj_Click);
            // 
            // RdbAlign16
            // 
            this.RdbAlign16.AutoSize = true;
            this.RdbAlign16.Checked = true;
            this.RdbAlign16.Location = new System.Drawing.Point(439, 7);
            this.RdbAlign16.Name = "RdbAlign16";
            this.RdbAlign16.Size = new System.Drawing.Size(121, 29);
            this.RdbAlign16.TabIndex = 5;
            this.RdbAlign16.TabStop = true;
            this.RdbAlign16.Text = "Align 16";
            this.RdbAlign16.UseVisualStyleBackColor = true;
            // 
            // RdbAlignNone
            // 
            this.RdbAlignNone.AutoSize = true;
            this.RdbAlignNone.Location = new System.Drawing.Point(575, 7);
            this.RdbAlignNone.Name = "RdbAlignNone";
            this.RdbAlignNone.Size = new System.Drawing.Size(148, 29);
            this.RdbAlignNone.TabIndex = 6;
            this.RdbAlignNone.Text = "Align None";
            this.RdbAlignNone.UseVisualStyleBackColor = true;
            // 
            // FrmMapEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1910, 877);
            this.Controls.Add(this.RdbAlignNone);
            this.Controls.Add(this.RdbAlign16);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.pnlView);
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "FrmMapEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Tile Map";
            this.Load += new System.EventHandler(this.FrmMapEditor_Load);
            this.pnlView.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picbo)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.PhiTieuObj)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Panel pnlView;
        private System.Windows.Forms.HScrollBar hScrollBar;
        private System.Windows.Forms.VScrollBar vScrollBar;
        private System.Windows.Forms.PictureBox picbo;
        private System.Windows.Forms.ToolStripButton tsbtnCreateMap;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton tsbtnSave;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsBtnClear;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.PictureBox PhiTieuObj;
        private System.Windows.Forms.ToolStripButton BtnUndo;
        private System.Windows.Forms.RadioButton RdbAlign16;
        private System.Windows.Forms.RadioButton RdbAlignNone;
    }
}

