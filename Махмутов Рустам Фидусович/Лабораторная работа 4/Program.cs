using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BTree
{
    class Program
    {
        static void Main(string[] args)
        {
            BTree tree = new BTree();
            tree.Degree = 3;

            Random rnd = new Random(DateTime.Now.Millisecond);
            for (int i = 0; i < 15; i++)
            {
                tree.Add(rnd.Next() % 100, DateTime.Now.ToString());
            }
            string ch = "";
            while (ch != "q")
            {

                Console.Clear();
                Console.WriteLine("[1] - Добавить");
                Console.WriteLine("[2] - Поиск");
                Console.WriteLine("[3] - Печать");
                Console.WriteLine("[4] - Удалить");
                Console.WriteLine("[q] - Выход");
                ch = Console.ReadLine();
                int x = 0;
                bool r = false;
                int ind = 0;
                string val = "";
                BTree newTree = null;


                try
                {
                    switch (ch)
                    {
                        case "1":

                            Console.WriteLine("Введите ключ для добавления в дерево");
                            x = Int32.Parse(Console.ReadLine());
                            Console.WriteLine("Введите значение для добавления в дерево");
                            val = Console.ReadLine();
                            if (tree.Add(x, val))
                            {
                                Console.WriteLine("Элемент добавлен");
                            }

                            else
                            {
                                Console.WriteLine("Элемент с таким ключом уже существует");
                            }


                            break;
                        case "2":

                            Console.WriteLine("Введите индекс");
                            x = Int32.Parse(Console.ReadLine());
                            if (tree.Search(x, ref val))
                            {
                                Console.WriteLine("Значение элемента = " + val.ToString());
                            }
                            else
                                Console.WriteLine("Элемент не найден");
                            break;
                        case "3":
                            Console.WriteLine("Содержимое дерева");
                            tree.Root?.Print(" ", false);
                            break;
                        case "4":
                            Console.WriteLine("Введите индекс");
                            ind = Int32.Parse(Console.ReadLine());
                            r = tree.Delete(ind, ref newTree);
                            if (r)
                            {
                                Console.WriteLine("Элемент удален");
                                tree = newTree;
                            }
                            else
                                Console.WriteLine("Элемент не найден");
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
