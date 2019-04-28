namespace SplitTools
{
    partial class frmCreateMap
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
            this.txtTileWidth = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtTileHeight = new System.Windows.Forms.TextBox();
            this.btnOk = new System.Windows.Forms.Button();
            this.LbPath = new System.Windows.Forms.Label();
            this.LbBrowser = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // txtTileWidth
            // 
            this.txtTileWidth.Location = new System.Drawing.Point(74, 7);
            this.txtTileWidth.Name = "txtTileWidth";
            this.txtTileWidth.Size = new System.Drawing.Size(204, 20);
            this.txtTileWidth.TabIndex = 5;
            this.txtTileWidth.Text = "16";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(52, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Tile width";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(56, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Tile height";
            // 
            // txtTileHeight
            // 
            this.txtTileHeight.Location = new System.Drawing.Point(74, 36);
            this.txtTileHeight.Name = "txtTileHeight";
            this.txtTileHeight.Size = new System.Drawing.Size(204, 20);
            this.txtTileHeight.TabIndex = 6;
            this.txtTileHeight.Text = "16";
            // 
            // btnOk
            // 
            this.btnOk.Location = new System.Drawing.Point(203, 94);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(75, 23);
            this.btnOk.TabIndex = 11;
            this.btnOk.Text = "OK";
            this.btnOk.UseVisualStyleBackColor = true;
            this.btnOk.Click += new System.EventHandler(this.btnOk_Click);
            // 
            // LbPath
            // 
            this.LbPath.AutoSize = true;
            this.LbPath.Location = new System.Drawing.Point(71, 71);
            this.LbPath.Name = "LbPath";
            this.LbPath.Size = new System.Drawing.Size(28, 13);
            this.LbPath.TabIndex = 13;
            this.LbPath.Text = "path";
            // 
            // LbBrowser
            // 
            this.LbBrowser.AutoSize = true;
            this.LbBrowser.Location = new System.Drawing.Point(13, 71);
            this.LbBrowser.Name = "LbBrowser";
            this.LbBrowser.Size = new System.Drawing.Size(40, 13);
            this.LbBrowser.TabIndex = 14;
            this.LbBrowser.TabStop = true;
            this.LbBrowser.Text = "Brower";
            this.LbBrowser.Click += new System.EventHandler(this.OpenBrowser);
            // 
            // frmCreateMap
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(290, 129);
            this.Controls.Add(this.LbBrowser);
            this.Controls.Add(this.LbPath);
            this.Controls.Add(this.txtTileHeight);
            this.Controls.Add(this.btnOk);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txtTileWidth);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "frmCreateMap";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Browse Map";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtTileWidth;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtTileHeight;
        private System.Windows.Forms.Button btnOk;
        private System.Windows.Forms.Label LbPath;
        private System.Windows.Forms.LinkLabel LbBrowser;
    }
}