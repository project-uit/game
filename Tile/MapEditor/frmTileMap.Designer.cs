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
            this.vScrollBar = new System.Windows.Forms.VScrollBar();
            this.hScrollBar = new System.Windows.Forms.HScrollBar();
            this.pnlView = new System.Windows.Forms.Panel();
            this.picbo = new System.Windows.Forms.PictureBox();
            this.tsbtnCreateMap = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbtnSave = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsBtnClear = new System.Windows.Forms.ToolStripButton();
            this.pnlView.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picbo)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // vScrollBar
            // 
            this.vScrollBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.vScrollBar.Location = new System.Drawing.Point(1696, 0);
            this.vScrollBar.Name = "vScrollBar";
            this.vScrollBar.Size = new System.Drawing.Size(17, 506);
            this.vScrollBar.TabIndex = 0;
            this.vScrollBar.ValueChanged += new System.EventHandler(this.VScrollBar_ValueChanged);
            // 
            // hScrollBar
            // 
            this.hScrollBar.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.hScrollBar.Location = new System.Drawing.Point(0, 506);
            this.hScrollBar.Name = "hScrollBar";
            this.hScrollBar.Size = new System.Drawing.Size(1696, 17);
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
            this.pnlView.Location = new System.Drawing.Point(0, 65);
            this.pnlView.Margin = new System.Windows.Forms.Padding(6);
            this.pnlView.Name = "pnlView";
            this.pnlView.Size = new System.Drawing.Size(1732, 546);
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
            this.tsBtnClear});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Padding = new System.Windows.Forms.Padding(0, 0, 4, 0);
            this.toolStrip1.Size = new System.Drawing.Size(1732, 39);
            this.toolStrip1.TabIndex = 1;
            this.toolStrip1.Text = "toolStrip1";
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
            // FrmMapEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1732, 613);
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
    }
}

