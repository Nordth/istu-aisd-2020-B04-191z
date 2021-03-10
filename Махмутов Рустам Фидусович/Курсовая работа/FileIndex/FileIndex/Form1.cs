using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FileIndex
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
        }

        
        class Word
        {
            public string Text { get; set; }
            public List<FileWord> Files = new List<FileWord>();
        }

        
        class FileWord
        {
            public FileWord()
            { }

             
            public FileWord(string word, string data)
            {
                this.Word = word;
                string[] parts = data.Split(new char[] { '>' }, StringSplitOptions.RemoveEmptyEntries);
                if (parts.Length == 2)
                {
                    this.Path = parts[0];
                    var ofs = parts[1].Split(new char[] { ',' }, StringSplitOptions.RemoveEmptyEntries);
                    foreach (var item in ofs)
                    {
                        this.Offsets.Add(Int32.Parse(item));
                    }
                }

            }

            
            public string Word { get; set; }
            
            public string Path { get; set; }
            
            public List<int> Offsets = new List<int>();

            
            public override string ToString()
            {
                
                StringBuilder sb = new StringBuilder();
                sb.Append(this.Path);
                sb.Append(">");
                foreach (var item in Offsets)
                {
                    sb.Append(item);
                    sb.Append(",");
                }
                return sb.ToString();
            }

        }
        private void btnSetPath_Click(object sender, EventArgs e)
        {
            
            FolderBrowserDialog dlg = new FolderBrowserDialog();

            if (dlg.ShowDialog() == DialogResult.OK)
            {
                
                txtPath.Text = dlg.SelectedPath;

            }
        }


        
        private void btnBuildIndex_Click(object sender, EventArgs e)
        {
            try
            {
                
                List<Word> wordList = new List<Word>();

                DirectoryInfo dir = new DirectoryInfo(txtPath.Text);
                FileInfo[] files = dir.GetFiles().Where(x => x.Extension == ".txt").ToArray();
                if (files.Count() == 0)
                {
                    MessageBox.Show("В указанной директории нет txt файлов");
                    return;
                }
                
                foreach (FileInfo file in files)
                {
                    List<FileWord> fileWords = new List<FileWord>();
                    string text = File.ReadAllText(file.FullName);
                    
                    if (text.Length == 0)
                        continue;
                    if (text[text.Length - 1] != ' ')
                    {
                        text += ' ';
                    }
                    
                    int i = 0;
                    int w = 0;
                    do
                    {
                        //если символ - проблел  или новая строка
                        if (text[i] == ' ' || text[i] == '\n')
                        {
                            
                            if (w != 0)
                            {
                                int offcet = i - w;
                                string word = text.Substring(i - w, w);
                                
                                word = Regex.Replace(word, "[-.?!)(,:]", "");
                                
                                var fileWord = fileWords.Where(x => x.Word == word).FirstOrDefault();
                                
                                if (fileWord == null)
                                {
                                    fileWord = new FileWord();
                                    fileWord.Word = word;
                                    fileWord.Path = file.FullName;
                                    fileWords.Add(fileWord);
                                }
                                 
                                fileWord.Offsets.Add(offcet);

                            }
                           
                            w = 0;
                        }
                        else
                        {
                            
                            w++;
                        }
                        
                        i++;

                    }
                    while (i < text.Length);
                    
                    foreach (var fileWord in fileWords)
                    {
                        var word = wordList.Where(x => x.Text == fileWord.Word).FirstOrDefault();
                        if (word == null)
                        {
                            word = new Word();
                            word.Text = fileWord.Word;
                            wordList.Add(word);
                        }
                        word.Files.Add(fileWord);
                    }
                }


                
                StringBuilder sb = new StringBuilder();
                foreach (var word in wordList)
                {
                    sb.Append(word.Text);
                    sb.Append(" ");
                    foreach (var file in word.Files)
                    {
                        sb.Append("<" + file.ToString());
                    }
                    sb.Append("\n");
                }
                
                File.WriteAllText(txtPath.Text + "\\index.dt", sb.ToString());
                MessageBox.Show("Индекс построен");
            }

            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void btnSort_Click(object sender, EventArgs e)
        {

        }



        private void btnFind_Click(object sender, EventArgs e)
        {

            try
            {
                if (!File.Exists(Path.Combine(txtPath.Text, "index.dt")))
                {
                    MessageBox.Show("не найден индекс");
                    return;
                }
                
                txtFind.Text = txtFind.Text.Trim();
                
                int border = 20;
                string index = File.ReadAllText(txtPath.Text + "\\index.dt");
                
                List<Word> wordList = new List<Word>();
                
                foreach (var lines in index.Split(new char[] { '\n' }, StringSplitOptions.RemoveEmptyEntries))
                {
                    
                    var parts = lines.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    string text = parts[0];
                    
                    string[] files = parts[1].Split(new char[] { '<' }, StringSplitOptions.RemoveEmptyEntries);
                    Word w = new Word();
                    w.Text = text;
                    foreach (var fl in files)
                    {
                        w.Files.Add(new FileWord(text, fl));
                    }
                    wordList.Add(w);
                }

                
                var word = wordList.Where(x => x.Text == txtFind.Text).FirstOrDefault();
                if (word == null)
                {
                    MessageBox.Show("Не найдено слово в индексном файле");
                    return;
                }

                
                StringBuilder sb = new StringBuilder();
                foreach (var fw in word.Files)
                {
                    var textFile = File.ReadAllText(fw.Path);
                    
                    sb.Append(Environment.NewLine);
                    sb.Append(Environment.NewLine);
                    sb.Append(fw.Path);
                    sb.Append(Environment.NewLine);
                    foreach (var of in fw.Offsets)
                    {
                        
                        var of2 = of - border > 0 ? of - border : 0;
                        sb.Append(textFile.Substring(of2, of2 + word.Text.Length + border * 2 < textFile.Length ? word.Text.Length + border * 2 : textFile.Length - of2));
                        sb.Append(Environment.NewLine);
                        sb.Append(Environment.NewLine);
                    }
                }

                lblResult.Text = sb.ToString();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }




}
