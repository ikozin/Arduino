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
            comboBoxPatterns = new ComboBox();
            btnAdd = new Button();
            btnFilter = new Button();
            SuspendLayout();
            // 
            // textBoxFilter
            // 
            textBoxFilter.AcceptsReturn = true;
            textBoxFilter.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            textBoxFilter.Location = new Point(3, 40);
            textBoxFilter.Multiline = true;
            textBoxFilter.Name = "textBoxFilter";
            textBoxFilter.ScrollBars = ScrollBars.Vertical;
            textBoxFilter.Size = new Size(226, 101);
            textBoxFilter.TabIndex = 0;
            // 
            // comboBoxPatterns
            // 
            comboBoxPatterns.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            comboBoxPatterns.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBoxPatterns.FormattingEnabled = true;
            comboBoxPatterns.Location = new Point(0, 147);
            comboBoxPatterns.Name = "comboBoxPatterns";
            comboBoxPatterns.Size = new Size(151, 28);
            comboBoxPatterns.TabIndex = 1;
            // 
            // btnAdd
            // 
            btnAdd.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            btnAdd.Location = new Point(160, 146);
            btnAdd.Name = "btnAdd";
            btnAdd.Size = new Size(69, 29);
            btnAdd.TabIndex = 2;
            btnAdd.Text = "Add";
            btnAdd.UseVisualStyleBackColor = true;
            btnAdd.Click += btnAdd_Click;
            // 
            // btnFilter
            // 
            btnFilter.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            btnFilter.Location = new Point(3, 5);
            btnFilter.Name = "btnFilter";
            btnFilter.Size = new Size(226, 29);
            btnFilter.TabIndex = 3;
            btnFilter.Text = "Отфильтровать";
            btnFilter.UseVisualStyleBackColor = true;
            btnFilter.Click += btnFilter_Click;
            // 
            // FilterFontCostructor
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(btnFilter);
            Controls.Add(btnAdd);
            Controls.Add(comboBoxPatterns);
            Controls.Add(textBoxFilter);
            Name = "FilterFontCostructor";
            Size = new Size(232, 178);
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        public TextBox textBoxFilter;
        private ComboBox comboBoxPatterns;
        private Button btnAdd;
        private Button btnFilter;
    }
}
