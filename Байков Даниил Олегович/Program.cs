using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TextIndex
{
    class Program
    {
        static void Main(string[] args)
        {
            //Дефолтный путь для файла индекса
            var indexFileName = "C:\\index.txt";

            while (true)
            {
                Console.WriteLine("1. Добавление новой индексируемой папки");
                Console.WriteLine("2. Поиск файлов в индексе по слову");

                var action = 0;

                int.TryParse( Console.ReadLine(), out action);

                switch (action)
                {
                    case 1:
                        Console.WriteLine("Укажите полный путь к индексируемой папке: ");
                        var folderPath = Console.ReadLine();
                        TextIndexer.IndexFolder(folderPath, indexFileName);
                        break;
                    case 2:
                        Console.WriteLine("Введите слово для поиска");
                        var findWord = Console.ReadLine();
                        Seeker.Seek(indexFileName, findWord);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
