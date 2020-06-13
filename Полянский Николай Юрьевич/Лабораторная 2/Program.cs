using System;
using System.Collections.Generic;
using Примеры;

namespace Структуры_данных
{
    class Program
    {
        static void Main(string[] args)
        {
            DoublyLinkedList<string> linkedList = new DoublyLinkedList<string>();

            Console.WriteLine("Двухсвязный список");
            Console.WriteLine("Отдельно введите 4 элемента.");

            linkedList.Add(Console.ReadLine());
            linkedList.Add(Console.ReadLine());
            linkedList.Add(Console.ReadLine());
            linkedList.Add(Console.ReadLine());

            Console.WriteLine("\nСписок:");

            linkedList.Print();

            Console.WriteLine("\nВведите новый элемент перед третьим элементом.");
            linkedList.AddBefore(Console.ReadLine(), 2);

            Console.WriteLine("\nСписок:\n");

            linkedList.Print();

            Console.WriteLine("\nДобавленный элемент по индексу [3-1] - " + linkedList.GetElement(2).ToString());

            Console.WriteLine("\nУдалите элемент по наименованию.");
            linkedList.Remove(Console.ReadLine());

            Console.WriteLine("\nСписок:");

            linkedList.Print();

            Console.Write("\nПоиск расстояния от индекса: ");
            int indexStart = Convert.ToInt32(Console.ReadLine());
            
            Console.Write("До индекса: ");
            int indexEnd = Convert.ToInt32(Console.ReadLine());

            Console.WriteLine($"Расстояние от индекса {indexStart} до {indexEnd} равно {linkedList.GetRange(indexStart, indexEnd)}");

            long totalMemory = GC.GetTotalMemory(false);

            Console.WriteLine($"\nЗанято памяти в куче до сборки мусора: {totalMemory}");

            Console.WriteLine("Очистка списка.");

            linkedList.Clear();

            long totalMemoryWithoutListElements = GC.GetTotalMemory(false);
            Console.WriteLine($"Занято памяти в куче после очистки списка: {totalMemoryWithoutListElements}");

            Console.WriteLine("Сборка мусора.");

            GC.Collect(1, GCCollectionMode.Forced);
            GC.WaitForPendingFinalizers();

            long totalMemoryWithoutTrash = GC.GetTotalMemory(false);
            Console.WriteLine($"Занято памяти в куче после сборки мусора: {totalMemoryWithoutTrash}");

            FixedStack<string> stackOne = new FixedStack<string>(2);

            try
            {
                Console.WriteLine("\nСтэк.");
                // добавляем четыре элемента
                Console.WriteLine("\nОтдельно добавьте 4 элемента.");
                stackOne.Push(Console.ReadLine());
                stackOne.Push(Console.ReadLine());
                stackOne.Push(Console.ReadLine());
                stackOne.Push(Console.ReadLine());

                Console.WriteLine("\nИзвлечение верхнего элемента.");
                // извлекаем один элемент
                var head = stackOne.Pop();

                Console.WriteLine($"Извлеченный элемент - {head}");
            }
            catch (InvalidOperationException ex)
            {
                Console.WriteLine(ex.Message);
            }

            Console.WriteLine($"\nЗанято памяти в куче до клонирования структуры: {totalMemory}");

            Console.WriteLine("Клонирование  структуры.");

            FixedStack<string> stackTwo = new FixedStack<string>(stackOne.Count);
            stackTwo = stackOne.Copy(stackTwo);

            long totalMemoryWithClone = GC.GetTotalMemory(false);
            Console.WriteLine($"Занято памяти в куче после клонирования структуры: {totalMemoryWithClone}");

            Console.WriteLine("Сборка мусора.");

            GC.Collect(1, GCCollectionMode.Forced);
            GC.WaitForPendingFinalizers();

            long MemoryWithoutTrash = GC.GetTotalMemory(false);
            Console.WriteLine($"Занято памяти в куче после сборки мусора: {MemoryWithoutTrash}");

            Console.Read();
        }
    }
}
