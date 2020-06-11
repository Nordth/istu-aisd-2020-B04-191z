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
            
            linkedList.Add("Employee #1");
            linkedList.Add("Employee #2");
            linkedList.Add("Employee #3");
            linkedList.Add("Employee #4");

            linkedList.Print();

            Console.WriteLine("Добавление элемента Employee #2.5 с индексом [2 - 1]");
            linkedList.AddBefore("Employee #2.5", 2);

            linkedList.Print();

            Console.WriteLine("Поиск по индексу " + linkedList.GetElement(2).ToString());

            Console.WriteLine("Удаление элемента Employee #2.5");
            linkedList.Remove("Employee #2.5");

            linkedList.Print();

            long totalMemory = GC.GetTotalMemory(false);

            Console.WriteLine($"Занято памяти в куче до сборки мусора: {totalMemory}");

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
                // добавляем четыре элемента
                Console.WriteLine("Добавление элементов Kate, Sam, Alice, Tom.");
                stackOne.Push("Kate");
                stackOne.Push("Sam");
                stackOne.Push("Alice");
                stackOne.Push("Tom");

                // извлекаем один элемент
                var head = stackOne.Pop();

                Console.WriteLine("Извлечение элемента Tom.");
                Console.WriteLine(head);    // Tom
            }
            catch (InvalidOperationException ex)
            {
                Console.WriteLine(ex.Message);
            }

            Console.WriteLine($"Занято памяти в куче до клонирования структуры: {totalMemory}");

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
