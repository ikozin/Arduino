namespace GenBinDefs
{
    partial class UserControlGenBinDefs
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
            ToolStripButton toolStripButtonTask;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(UserControlGenBinDefs));
            ToolStripSeparator toolStripSeparator;
            ToolStripButton toolStripButtonCopy;
            ToolStripButton toolStripButtonSave;
            textBoxDefs = new TextBox();
            saveFileDlg = new SaveFileDialog();
            panelPattern = new Panel();
            checkedListBox = new CheckedListBox();
            contextMenuStripList = new ContextMenuStrip(components);
            panelCommand = new Panel();
            btnPatternAdd = new Button();
            textBoxPattern = new TextBox();
            splitter = new Splitter();
            toolStripMenu = new ToolStrip();
            toolStripComboBoxLang = new ToolStripComboBox();
            toolStripMenuItemSelect = new ToolStripMenuItem();
            toolStripMenuItemDeselect = new ToolStripMenuItem();
            btnPatternDel = new Button();
            toolStripButtonTask = new ToolStripButton();
            toolStripSeparator = new ToolStripSeparator();
            toolStripButtonCopy = new ToolStripButton();
            toolStripButtonSave = new ToolStripButton();
            panelPattern.SuspendLayout();
            contextMenuStripList.SuspendLayout();
            panelCommand.SuspendLayout();
            toolStripMenu.SuspendLayout();
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
            btnPatternDel.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            btnPatternDel.Location = new Point(3, 3);
            btnPatternDel.Name = "btnPatternDel";
            btnPatternDel.Size = new Size(219, 29);
            btnPatternDel.TabIndex = 1;
            btnPatternDel.Text = "Удалить";
            btnPatternDel.UseVisualStyleBackColor = true;
            btnPatternDel.Click += BtnPatternDel_Click;
            // 
            // toolStripButtonTask
            // 
            toolStripButtonTask.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButtonTask.Image = (Image)resources.GetObject("toolStripButtonTask.Image");
            toolStripButtonTask.ImageTransparentColor = Color.Magenta;
            toolStripButtonTask.Name = "toolStripButtonTask";
            toolStripButtonTask.Size = new Size(59, 25);
            toolStripButtonTask.Text = "Запуск";
            toolStripButtonTask.Click += ToolStripButtonTask_Click;
            // 
            // toolStripSeparator
            // 
            toolStripSeparator.Name = "toolStripSeparator";
            toolStripSeparator.Size = new Size(6, 28);
            // 
            // toolStripButtonCopy
            // 
            toolStripButtonCopy.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButtonCopy.Image = (Image)resources.GetObject("toolStripButtonCopy.Image");
            toolStripButtonCopy.ImageTransparentColor = Color.Magenta;
            toolStripButtonCopy.Name = "toolStripButtonCopy";
            toolStripButtonCopy.Size = new Size(47, 25);
            toolStripButtonCopy.Text = "Copy";
            toolStripButtonCopy.Click += ToolStripButtonCopy_Click;
            // 
            // toolStripButtonSave
            // 
            toolStripButtonSave.DisplayStyle = ToolStripItemDisplayStyle.Text;
            toolStripButtonSave.Image = (Image)resources.GetObject("toolStripButtonSave.Image");
            toolStripButtonSave.ImageTransparentColor = Color.Magenta;
            toolStripButtonSave.Name = "toolStripButtonSave";
            toolStripButtonSave.Size = new Size(87, 25);
            toolStripButtonSave.Text = "Сохранить";
            toolStripButtonSave.Click += ToolStripButtonSave_Click;
            // 
            // textBoxDefs
            // 
            textBoxDefs.Dock = DockStyle.Fill;
            textBoxDefs.Font = new Font("Roboto", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            textBoxDefs.Location = new Point(232, 28);
            textBoxDefs.Multiline = true;
            textBoxDefs.Name = "textBoxDefs";
            textBoxDefs.ReadOnly = true;
            textBoxDefs.ScrollBars = ScrollBars.Both;
            textBoxDefs.Size = new Size(547, 366);
            textBoxDefs.TabIndex = 1;
            textBoxDefs.WordWrap = false;
            // 
            // saveFileDlg
            // 
            saveFileDlg.Filter = "Все файлы|*.*";
            // 
            // panelPattern
            // 
            panelPattern.BorderStyle = BorderStyle.Fixed3D;
            panelPattern.Controls.Add(checkedListBox);
            panelPattern.Controls.Add(panelCommand);
            panelPattern.Dock = DockStyle.Left;
            panelPattern.Location = new Point(0, 28);
            panelPattern.Name = "panelPattern";
            panelPattern.Size = new Size(226, 366);
            panelPattern.TabIndex = 2;
            // 
            // checkedListBox
            // 
            checkedListBox.ContextMenuStrip = contextMenuStripList;
            checkedListBox.Dock = DockStyle.Fill;
            checkedListBox.FormattingEnabled = true;
            checkedListBox.Location = new Point(0, 0);
            checkedListBox.Name = "checkedListBox";
            checkedListBox.ScrollAlwaysVisible = true;
            checkedListBox.Size = new Size(222, 289);
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
            panelCommand.Location = new Point(0, 289);
            panelCommand.Name = "panelCommand";
            panelCommand.Size = new Size(222, 73);
            panelCommand.TabIndex = 4;
            // 
            // btnPatternAdd
            // 
            btnPatternAdd.Anchor = AnchorStyles.Top | AnchorStyles.Right;
            btnPatternAdd.Location = new Point(131, 37);
            btnPatternAdd.Name = "btnPatternAdd";
            btnPatternAdd.Size = new Size(88, 29);
            btnPatternAdd.TabIndex = 3;
            btnPatternAdd.Text = "Добавить";
            btnPatternAdd.UseVisualStyleBackColor = true;
            // 
            // textBoxPattern
            // 
            textBoxPattern.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
            textBoxPattern.Location = new Point(3, 38);
            textBoxPattern.Name = "textBoxPattern";
            textBoxPattern.Size = new Size(125, 27);
            textBoxPattern.TabIndex = 2;
            // 
            // splitter
            // 
            splitter.Location = new Point(226, 28);
            splitter.MinExtra = 226;
            splitter.Name = "splitter";
            splitter.Size = new Size(6, 366);
            splitter.TabIndex = 3;
            splitter.TabStop = false;
            // 
            // toolStripMenu
            // 
            toolStripMenu.ImageScalingSize = new Size(20, 20);
            toolStripMenu.Items.AddRange(new ToolStripItem[] { toolStripComboBoxLang, toolStripButtonTask, toolStripSeparator, toolStripButtonCopy, toolStripButtonSave });
            toolStripMenu.Location = new Point(0, 0);
            toolStripMenu.Name = "toolStripMenu";
            toolStripMenu.Size = new Size(779, 28);
            toolStripMenu.TabIndex = 15;
            toolStripMenu.Text = "toolStrip1";
            // 
            // toolStripComboBoxLang
            // 
            toolStripComboBoxLang.DropDownStyle = ComboBoxStyle.DropDownList;
            toolStripComboBoxLang.Name = "toolStripComboBoxLang";
            toolStripComboBoxLang.Size = new Size(121, 28);
            toolStripComboBoxLang.SelectedIndexChanged += ToolStripComboBoxLang_SelectedIndexChanged;
            // 
            // UserControlGenBinDefs
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            Controls.Add(textBoxDefs);
            Controls.Add(splitter);
            Controls.Add(panelPattern);
            Controls.Add(toolStripMenu);
            Name = "UserControlGenBinDefs";
            Size = new Size(779, 394);
            panelPattern.ResumeLayout(false);
            contextMenuStripList.ResumeLayout(false);
            panelCommand.ResumeLayout(false);
            panelCommand.PerformLayout();
            toolStripMenu.ResumeLayout(false);
            toolStripMenu.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
        private TextBox textBoxDefs;
        private SaveFileDialog saveFileDlg;
        private Panel panelPattern;
        private Splitter splitter;
        private CheckedListBox checkedListBox;
        private ContextMenuStrip contextMenuStripList;
        private TextBox textBoxPattern;
        private Button btnPatternAdd;
        private Panel panelCommand;
        private ToolStrip toolStripMenu;
        private ToolStripComboBox toolStripComboBoxLang;
    }
}
