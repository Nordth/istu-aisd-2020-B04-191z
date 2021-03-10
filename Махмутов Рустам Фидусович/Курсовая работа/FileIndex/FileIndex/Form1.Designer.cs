
namespace FileIndex
{
    partial class FormMain
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnSetPath = new System.Windows.Forms.Button();
            this.txtPath = new System.Windows.Forms.TextBox();
            this.btnBuildIndex = new System.Windows.Forms.Button();
            this.txtFind = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnFind = new System.Windows.Forms.Button();
            this.lblResult = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // btnSetPath
            // 
            this.btnSetPath.Location = new System.Drawing.Point(192, 34);
            this.btnSetPath.Name = "btnSetPath";
            this.btnSetPath.Size = new System.Drawing.Size(176, 23);
            this.btnSetPath.TabIndex = 0;
            this.btnSetPath.Text = "Указать директорию";
            this.btnSetPath.UseVisualStyleBackColor = true;
            this.btnSetPath.Click += new System.EventHandler(this.btnSetPath_Click);
            // 
            // txtPath
            // 
            this.txtPath.Location = new System.Drawing.Point(12, 36);
            this.txtPath.Name = "txtPath";
            this.txtPath.Size = new System.Drawing.Size(174, 20);
            this.txtPath.TabIndex = 1;
            // 
            // btnBuildIndex
            // 
            this.btnBuildIndex.Location = new System.Drawing.Point(375, 36);
            this.btnBuildIndex.Name = "btnBuildIndex";
            this.btnBuildIndex.Size = new System.Drawing.Size(75, 23);
            this.btnBuildIndex.TabIndex = 2;
            this.btnBuildIndex.Text = "Построить индекс";
            this.btnBuildIndex.UseVisualStyleBackColor = true;
            this.btnBuildIndex.Click += new System.EventHandler(this.btnBuildIndex_Click);
            // 
            // txtFind
            // 
            this.txtFind.Location = new System.Drawing.Point(86, 62);
            this.txtFind.Name = "txtFind";
            this.txtFind.Size = new System.Drawing.Size(100, 20);
            this.txtFind.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 68);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(39, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Поиск";
            // 
            // btnFind
            // 
            this.btnFind.Location = new System.Drawing.Point(192, 59);
            this.btnFind.Name = "btnFind";
            this.btnFind.Size = new System.Drawing.Size(176, 23);
            this.btnFind.TabIndex = 6;
            this.btnFind.Text = "Найти";
            this.btnFind.UseVisualStyleBackColor = true;
            this.btnFind.Click += new System.EventHandler(this.btnFind_Click);
            // 
            // lblResult
            // 
            this.lblResult.AutoSize = true;
            this.lblResult.Location = new System.Drawing.Point(16, 114);
            this.lblResult.Name = "lblResult";
            this.lblResult.Size = new System.Drawing.Size(0, 13);
            this.lblResult.TabIndex = 7;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.lblResult);
            this.Controls.Add(this.btnFind);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtFind);
            this.Controls.Add(this.btnBuildIndex);
            this.Controls.Add(this.txtPath);
            this.Controls.Add(this.btnSetPath);
            this.Name = "FormMain";
            this.Text = "Индексатор файлов";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnSetPath;
        private System.Windows.Forms.TextBox txtPath;
        private System.Windows.Forms.Button btnBuildIndex;
        private System.Windows.Forms.TextBox txtFind;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnFind;
        private System.Windows.Forms.Label lblResult;
    }
}

