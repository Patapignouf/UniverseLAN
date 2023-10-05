﻿namespace UniverseLanWizard
{
    partial class WizardInstallUniverseLANForm
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
            this.txtbox_game_directory = new System.Windows.Forms.TextBox();
            this.btn_browse_game_directory = new System.Windows.Forms.Button();
            this.label_game_directory = new System.Windows.Forms.Label();
            this.table_layout_panel_game_directory = new System.Windows.Forms.TableLayoutPanel();
            this.btn_scan = new System.Windows.Forms.Button();
            this.table_layout_panel_game_directory.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtbox_game_directory
            // 
            this.txtbox_game_directory.AllowDrop = true;
            this.txtbox_game_directory.AutoCompleteMode = System.Windows.Forms.AutoCompleteMode.SuggestAppend;
            this.txtbox_game_directory.AutoCompleteSource = System.Windows.Forms.AutoCompleteSource.FileSystem;
            this.txtbox_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtbox_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtbox_game_directory.Location = new System.Drawing.Point(113, 3);
            this.txtbox_game_directory.Name = "txtbox_game_directory";
            this.txtbox_game_directory.Size = new System.Drawing.Size(684, 22);
            this.txtbox_game_directory.TabIndex = 0;
            this.txtbox_game_directory.WordWrap = false;
            this.txtbox_game_directory.TextChanged += new System.EventHandler(this.txtbox_game_directory_TextChanged);
            // 
            // btn_browse_game_directory
            // 
            this.btn_browse_game_directory.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btn_browse_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btn_browse_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_browse_game_directory.Location = new System.Drawing.Point(803, 3);
            this.btn_browse_game_directory.Name = "btn_browse_game_directory";
            this.btn_browse_game_directory.Size = new System.Drawing.Size(104, 29);
            this.btn_browse_game_directory.TabIndex = 1;
            this.btn_browse_game_directory.Text = "Browse...";
            this.btn_browse_game_directory.UseVisualStyleBackColor = true;
            this.btn_browse_game_directory.Click += new System.EventHandler(this.btn_browse_game_directory_Click);
            // 
            // label_game_directory
            // 
            this.label_game_directory.AutoSize = true;
            this.label_game_directory.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label_game_directory.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_game_directory.Location = new System.Drawing.Point(3, 0);
            this.label_game_directory.Name = "label_game_directory";
            this.label_game_directory.Size = new System.Drawing.Size(104, 35);
            this.label_game_directory.TabIndex = 2;
            this.label_game_directory.Text = "Game Directory:";
            this.label_game_directory.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // table_layout_panel_game_directory
            // 
            this.table_layout_panel_game_directory.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.table_layout_panel_game_directory.ColumnCount = 3;
            this.table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.table_layout_panel_game_directory.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.table_layout_panel_game_directory.Controls.Add(this.btn_browse_game_directory, 2, 0);
            this.table_layout_panel_game_directory.Controls.Add(this.txtbox_game_directory, 1, 0);
            this.table_layout_panel_game_directory.Controls.Add(this.label_game_directory, 0, 0);
            this.table_layout_panel_game_directory.Controls.Add(this.btn_scan, 2, 1);
            this.table_layout_panel_game_directory.Location = new System.Drawing.Point(12, 12);
            this.table_layout_panel_game_directory.Name = "table_layout_panel_game_directory";
            this.table_layout_panel_game_directory.RowCount = 2;
            this.table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.table_layout_panel_game_directory.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.table_layout_panel_game_directory.Size = new System.Drawing.Size(910, 71);
            this.table_layout_panel_game_directory.TabIndex = 3;
            // 
            // btn_scan
            // 
            this.btn_scan.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btn_scan.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btn_scan.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_scan.Location = new System.Drawing.Point(803, 38);
            this.btn_scan.Name = "btn_scan";
            this.btn_scan.Size = new System.Drawing.Size(104, 30);
            this.btn_scan.TabIndex = 5;
            this.btn_scan.Text = "Scan";
            this.btn_scan.UseVisualStyleBackColor = true;
            // 
            // WizardInstallUniverseLANForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(934, 503);
            this.Controls.Add(this.table_layout_panel_game_directory);
            this.MinimumSize = new System.Drawing.Size(312, 132);
            this.Name = "WizardInstallUniverseLANForm";
            this.Text = "Install UniverseLAN";
            this.Load += new System.EventHandler(this.WizardInstallUniverseLANForm_Load);
            this.table_layout_panel_game_directory.ResumeLayout(false);
            this.table_layout_panel_game_directory.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox txtbox_game_directory;
        private System.Windows.Forms.Button btn_browse_game_directory;
        private System.Windows.Forms.Label label_game_directory;
        private System.Windows.Forms.TableLayoutPanel table_layout_panel_game_directory;
        private System.Windows.Forms.Button btn_scan;
    }
}

