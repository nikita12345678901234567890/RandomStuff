namespace Pong
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.button = new System.Windows.Forms.PictureBox();
            this.RStan = new System.Windows.Forms.PictureBox();
            this.LStan = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.button)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.RStan)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.LStan)).BeginInit();
            this.SuspendLayout();
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 17;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // button
            // 
            this.button.Image = ((System.Drawing.Image)(resources.GetObject("button.Image")));
            this.button.Location = new System.Drawing.Point(12, 12);
            this.button.Name = "button";
            this.button.Size = new System.Drawing.Size(75, 75);
            this.button.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.button.TabIndex = 0;
            this.button.TabStop = false;
            // 
            // RStan
            // 
            this.RStan.Image = ((System.Drawing.Image)(resources.GetObject("RStan.Image")));
            this.RStan.Location = new System.Drawing.Point(128, 114);
            this.RStan.Name = "RStan";
            this.RStan.Size = new System.Drawing.Size(100, 100);
            this.RStan.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.RStan.TabIndex = 1;
            this.RStan.TabStop = false;
            this.RStan.Visible = false;
            // 
            // LStan
            // 
            this.LStan.Image = ((System.Drawing.Image)(resources.GetObject("LStan.Image")));
            this.LStan.Location = new System.Drawing.Point(12, 114);
            this.LStan.Name = "LStan";
            this.LStan.Size = new System.Drawing.Size(100, 100);
            this.LStan.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.LStan.TabIndex = 2;
            this.LStan.TabStop = false;
            this.LStan.Visible = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(234, 211);
            this.Controls.Add(this.LStan);
            this.Controls.Add(this.RStan);
            this.Controls.Add(this.button);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "Form1";
            this.Text = "Form1";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyUp);
            ((System.ComponentModel.ISupportInitialize)(this.button)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.RStan)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.LStan)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timer1;
        private PictureBox button;
        private PictureBox RStan;
        private PictureBox LStan;
    }
}