namespace GenBinDefs
{
    partial class FilterGenBinDefs
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
            components = new System.ComponentModel.Container();
            ToolStripMenuItem toolStripMenuItemSelect;
            ToolStripMenuItem toolStripMenuItemDeselect;
            Button btnPatternDel;
            Button btnPatternAdd;
            panelPattern = new Panel();
            checkedListBox = new CheckedListBox();
            contextMenuStripList = new ContextMenuStrip(components);
            panelCommand = new Panel();
            textBoxPattern = new TextBox();
            toolStripMenuItemSelect = new ToolStripMenuItem();
            toolStripMenuItemDeselect = new ToolStripMenuItem();
            btnPatternDel = new Button();
            btnPatternAdd = new Button();
            panelPattern.SuspendLayout();
            contextMenuStripList.SuspendLayout();
            panelCommand.SuspendLayout();
            SuspendLayout();
            // 
            // toolStripMenuItemSelect
            // 
            toolStripMenuItemSelect.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripMenuItemSelect.Name = "toolStripMenuItemSelect";
            toolStripMenuItemSelect.Size = new Size(199, 24);
            toolStripMenuItemSelect.Tag = "True";
            toolStripMenuItemSelect.Text = "Выбрть всё";
            toolStripMenuItemSelect.Click += ToolStripMenuItemList_Click;
            // 
            // toolStripMenuItemDeselect
            // 
            toolStripMenuItemDeselect.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripMenuItemDeselect.Name = "toolStripMenuItemDeselect";
            toolStripMenuItemDeselect.Size = new Size(199, 24);
            toolStripMenuItemDeselect.Tag = "False";
            toolStripMenuItemDeselect.Text = "Снять выделение";
            toolStripMenuItemDeselect.Click += ToolStripMenuItemList_Click;
            // 
            // btnPatternDel
            // 
            btnPatternDel.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            btnPatternDel.Location = new Point(3, 3);
            btnPatternDel.Name = "btnPatternDel";
            btnPatternDel.Size = new Size(219, 29);
            btnPatternDel.TabIndex = 1;
            btnPatternDel.Text = "Удалить";
            btnPatternDel.UseVisualStyleBackColor = true;
            btnPatternDel.Click += BtnPatternDel_Click;
            // 
            // panelPattern
            // 
            panelPattern.BorderStyle = BorderStyle.Fixed3D;
            panelPattern.Controls.Add(checkedListBox);
            panelPattern.Controls.Add(panelCommand);
            panelPattern.Dock = DockStyle.Fill;
            panelPattern.Location = new Point(0, 0);
            panelPattern.Name = "panelPattern";
            panelPattern.Size = new Size(226, 394);
            panelPattern.TabIndex = 2;
            // 
            // checkedListBox
            // 
            checkedListBox.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            checkedListBox.ContextMenuStrip = contextMenuStripList;
            checkedListBox.FormattingEnabled = true;
            checkedListBox.Location = new Point(0, 0);
            checkedListBox.Name = "checkedListBox";
            checkedListBox.ScrollAlwaysVisible = true;
            checkedListBox.Size = new Size(222, 312);
            checkedListBox.TabIndex = 0;
            // 
            // contextMenuStripList
            // 
            contextMenuStripList.ImageScalingSize = new Size(20, 20);
            contextMenuStripList.Items.AddRange(new ToolStripItem[] { toolStripMenuItemSelect, toolStripMenuItemDeselect });
            contextMenuStripList.Name = "contextMenuStripList";
            contextMenuStripList.Size = new Size(200, 52);
            // 
            // panelCommand
            // 
            panelCommand.Controls.Add(btnPatternAdd);
            panelCommand.Controls.Add(btnPatternDel);
            panelCommand.Controls.Add(textBoxPattern);
            panelCommand.Dock = DockStyle.Bottom;
            panelCommand.Location = new Point(0, 317);
            panelCommand.Name = "panelCommand";
            panelCommand.Size = new Size(222, 73);
            panelCommand.TabIndex = 4;
            // 
            // btnPatternAdd
            // 
            btnPatternAdd.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            btnPatternAdd.Location = new Point(131, 37);
            btnPatternAdd.Name = "btnPatternAdd";
            btnPatternAdd.Size = new Size(88, 29);
            btnPatternAdd.TabIndex = 3;
            btnPatternAdd.Text = "Добавить";
            btnPatternAdd.UseVisualStyleBackColor = true;
            btnPatternAdd.Click += btnPatternAdd_Click;
            // 
            // textBoxPattern
            // 
            textBoxPattern.Anchor = AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
            textBoxPattern.Location = new Point(3, 38);
            textBoxPattern.Name = "textBoxPattern";
            textBoxPattern.Size = new Size(125, 27);
            textBoxPattern.TabIndex = 2;
            // 
            // FilterGenBinDefs
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(panelPattern);
            Name = "FilterGenBinDefs";
            Size = new Size(226, 394);
            panelPattern.ResumeLayout(false);
            contextMenuStripList.ResumeLayout(false);
            panelCommand.ResumeLayout(false);
            panelCommand.PerformLayout();
            ResumeLayout(false);
        }

        #endregion
        private Panel panelPattern;
        private CheckedListBox checkedListBox;
        private ContextMenuStrip contextMenuStripList;
        private TextBox textBoxPattern;
        private Button btnPatternAdd;
        private Panel panelCommand;
    }
}
