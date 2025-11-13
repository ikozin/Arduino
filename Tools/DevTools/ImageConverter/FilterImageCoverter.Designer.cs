namespace ImageConverter
{
    partial class FilterImageCoverter
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            Label labelHeigth;
            Label labelWidth;
            textBoxHeight = new TextBox();
            textBoxWidth = new TextBox();
            labelHeigth = new Label();
            labelWidth = new Label();
            SuspendLayout();
            // 
            // labelHeigth
            // 
            labelHeigth.AutoSize = true;
            labelHeigth.Location = new Point(132, 6);
            labelHeigth.Name = "labelHeigth";
            labelHeigth.Size = new Size(59, 20);
            labelHeigth.TabIndex = 6;
            labelHeigth.Text = "Высота";
            // 
            // labelWidth
            // 
            labelWidth.AutoSize = true;
            labelWidth.Location = new Point(2, 6);
            labelWidth.Name = "labelWidth";
            labelWidth.Size = new Size(67, 20);
            labelWidth.TabIndex = 4;
            labelWidth.Text = "Ширина";
            // 
            // textBoxHeight
            // 
            textBoxHeight.Location = new Point(197, 3);
            textBoxHeight.Name = "textBoxHeight";
            textBoxHeight.ReadOnly = true;
            textBoxHeight.Size = new Size(47, 27);
            textBoxHeight.TabIndex = 7;
            textBoxHeight.Text = "0";
            textBoxHeight.WordWrap = false;
            // 
            // textBoxWidth
            // 
            textBoxWidth.Location = new Point(74, 3);
            textBoxWidth.Name = "textBoxWidth";
            textBoxWidth.ReadOnly = true;
            textBoxWidth.Size = new Size(47, 27);
            textBoxWidth.TabIndex = 5;
            textBoxWidth.Text = "0";
            textBoxWidth.WordWrap = false;
            // 
            // FilterImageCoverter
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BorderStyle = BorderStyle.Fixed3D;
            Controls.Add(textBoxHeight);
            Controls.Add(labelHeigth);
            Controls.Add(textBoxWidth);
            Controls.Add(labelWidth);
            Name = "FilterImageCoverter";
            Size = new Size(245, 273);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private TextBox textBoxHeight;
        private TextBox textBoxWidth;
    }
}
