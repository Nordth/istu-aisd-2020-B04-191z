using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace TextIndex
{
    public class TextIndexer
    {
        /// <summary>
        /// Мето для создания или дополнения файла индекса
        /// </summary>
        /// <param name="folderPath">Путь до папки с индексируемыми файлами</param>
        /// <param name="indexFileName">Имя файла индекса</param>
        public static void IndexFolder(string folderPath, string indexFileName)
        {

            if (!Directory.Exists(folderPath)) { Console.WriteLine("Такой папки нет."); return; }

            var textIndex = new TextIndex();

            if (File.Exists(indexFileName))
            {
                textIndex = JsonConvert.DeserializeObject<TextIndex>(File.ReadAllText(indexFileName));
            }

            var files = Directory.GetFiles(folderPath);

            if (files.Length == 0) { Console.WriteLine("В папке нет файлов для индексирования"); return; }

            foreach (var file in files)
            {

                var indexes = new List<WordIndex>();
                var splitter = new char[] { ' ', '.', ',', '…' }.ToList();
                var rows = File.ReadAllLines(file);
                for (int i = 0; i < rows.Length; i++)
                {
                    var row = rows[i];
                    var word = "";

                    for (int j = 0; j < row.Length; j++)
                    {
                        var symbol = row[j];
                        var isMatch = Regex.IsMatch(symbol.ToString(), "[а-яА-Я0-9a-zA-Z]{1}");
                        if (isMatch) { word += symbol; }
                        else
                        {
                            if (word == "") { continue; }
                            var wordindex = j - word.Length;

                            var existedindex = indexes.FirstOrDefault(x => x.Word == word);
                            if (existedindex == null)
                            {
                                var t = new WordIndex();
                                t.Word = word;
                                t.RowOffset.Add(new WordOffset() { Row = i, Offset = wordindex });
                                indexes.Add(t);
                            }

                            else { existedindex.RowOffset.Add(new WordOffset() { Row = i, Offset = wordindex }); }

                            word = "";
                        }
                    }
                    if (word != "")
                    {
                        var wordindex = row.Length - word.Length;

                        var existedindex = indexes.FirstOrDefault(x => x.Word == word);
                        if (existedindex == null)
                        {
                            var t = new WordIndex();
                            t.Word = word;
                            t.RowOffset.Add(new WordOffset() { Row = i, Offset = wordindex });
                            indexes.Add(t);
                        }
                        else { existedindex.RowOffset.Add(new WordOffset() { Row = i, Offset = wordindex }); }
                    }
                }
                textIndex.Files.Add(new FileIndex { Name = file, Words = indexes });

            }

            var serializedIndex = JsonConvert.SerializeObject(textIndex,Formatting.Indented);

            File.WriteAllText(indexFileName, serializedIndex);

            Console.WriteLine("Индексирвоание файла выполнено.");
        }
    }
}
