using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextIndex
{
    public class Seeker
    {
        /// <summary>
        /// Метод поиска слова в индексируемом файле
        /// </summary>
        /// <param name="indexFileName">Путь до файла индекса</param>
        /// <param name="findWord">Искомое слово</param>
        public static void Seek (string indexFileName, string findWord)
        {

            if (!File.Exists(indexFileName)) { Console.WriteLine("Нет файла индекса."); return; }


            var readIndex = JsonConvert.DeserializeObject<TextIndex>(File.ReadAllText(indexFileName));

            foreach (var fileIndex in readIndex.Files)
            {
                foreach (var word1 in fileIndex.Words)
                {
                    if (word1.Word == findWord)
                    {
                        Console.WriteLine($"Найдено слово {word1.Word} в файле {fileIndex.Name}: ");
                        foreach (var offset in word1.RowOffset)
                        {
                            var findstring = File.ReadAllLines(fileIndex.Name)[offset.Row];
                            Console.WriteLine($"Смещение: {offset.Row}") ;
                            Console.WriteLine(findstring);
                        }
                    }
                }
            }
        }
    }
}
