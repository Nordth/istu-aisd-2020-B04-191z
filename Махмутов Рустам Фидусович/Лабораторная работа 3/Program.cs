using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HashTable
{
    class Program
    {
        static void Main(string[] args)
        {
            HashTable tbl = new HashTable(100);
            string ch = "";
            while (ch != "q")
            {
                Console.Clear();
                Console.WriteLine("[1] - Добавление");
                Console.WriteLine("[2] - Запись");
                Console.WriteLine("[3] - Поиск");
                Console.WriteLine("[4] - Удаление");
                Console.WriteLine("[q] - Выход");
                ch = Console.ReadLine();
                int x = 0;
                bool r = false;
                int ind = 0;
                string y = "";
                try
                {
                    switch (ch)
                    {
                        case "1":

                            Console.WriteLine("Введите индекс");
                            x = Int32.Parse(Console.ReadLine());
                            Console.WriteLine("Введите значение");
                            y = Console.ReadLine();
                            if (tbl.addValue(x, y))
                                Console.WriteLine("Элемент добавлен");
                            else
                                Console.WriteLine("Элемент с указанным ключом уже существует");

                            break;
                        case "2":

                            Console.WriteLine("Введите индекс");
                            x = Int32.Parse(Console.ReadLine());
                            Console.WriteLine("Введите значение");
                            y = Console.ReadLine();
                            if (tbl.setValue(x, y))
                                Console.WriteLine("Элемент изменен");
                            else
                                Console.WriteLine("Элемент с указанным ключом не существует");


                            break;
                        case "3":

                            Console.WriteLine("Введите индекс");
                            x = Int32.Parse(Console.ReadLine());
                            if (tbl.getValue(x, ref y))
                                Console.WriteLine("Значение  = {0}", y);
                            else
                                Console.WriteLine("Элемент не найден");
                            break;
                        case "4":
                            Console.WriteLine("Введите индекс");
                            ind = Int32.Parse(Console.ReadLine());
                            if (tbl.cleanValue(ind))
                                Console.WriteLine("Элемент удален");
                            else
                                Console.WriteLine("Элемент с указанным ключом не существует");
                            break;

                        default:
                            break;
                    }
                }
                catch (Exception ex) { Console.WriteLine("Ошибка входных данных, {0}", ex.Message); }
                Console.WriteLine("Нажмите любую кнопку для продолжения");
                Console.ReadKey();

            }
        }
    }
}
