namespace FontCostructor
{
    partial class FilterFontCostructor
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
            textBoxFilter = new TextBox();
            SuspendLayout();
            // 
            // textBoxFilter
            // 
            textBoxFilter.AcceptsReturn = true;
            textBoxFilter.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            textBoxFilter.Location = new Point(3, 3);
            textBoxFilter.Multiline = true;
            textBoxFilter.Name = "textBoxFilter";
            textBoxFilter.ScrollBars = ScrollBars.Vertical;
            textBoxFilter.Size = new Size(144, 114);
            textBoxFilter.TabIndex = 0;
            // 
            // FilterFontCostructor
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(textBoxFilter);
            Name = "FilterFontCostructor";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        public TextBox textBoxFilter;
    }
}
