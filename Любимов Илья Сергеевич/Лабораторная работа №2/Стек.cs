using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

namespace Stack
{
    class Program
    {
        static void Main(string[] args)
        {
            Stack<string> stack = new Stack<string>();
            Stack<string> stack_copy = new Stack<string>(); ;
            int i,d=0;
        start:
            Console.WriteLine("============Содержание============");
            if (stack.IsEmpty)
            {
                Console.WriteLine("Пусто");
            }
            else
            {
                if (d == 0) stack.List();
                else if (d == 1) stack_copy.List();
            }
            Console.WriteLine("==================================");
            if (d == 0) Console.WriteLine("Activ stec: Оригинал");
            else if(d == 1) Console.WriteLine("Activ stec: Копия");


            Console.WriteLine("Выберите действие:");
            Console.WriteLine("1.Вставка на вершину стека.");
            Console.WriteLine("2.Вставка в конец очереди.");
            Console.WriteLine("3.Извлечение с вершины стека.");
            Console.WriteLine("4.Извлечение из начала очереди.");
            Console.WriteLine("5.Освобождение памяти от структуры данных.");
            Console.WriteLine("6.Клонировать оригинал.");
            Console.WriteLine("7.Выбор стека.");
            Console.Write("Введите номер действия: ");
            i = int.Parse(Console.ReadLine());

            if (i == 1)
            {
                Console.Clear();
                Console.Write("Введите значение: ");
                if (d == 0) stack.Push(Console.ReadLine());
                else if (d == 1) stack_copy.Push(Console.ReadLine());
                Console.WriteLine("Значение добавлено!");
                Thread.Sleep(400);
                Console.Clear();
                goto start;
            }
            else if (i == 2)
            {
                Console.Clear();
                Console.Write("Введите значение: ");
                if (d == 0) stack.PushLast(Console.ReadLine());
                else if (d == 1) stack_copy.PushLast(Console.ReadLine());
                Console.WriteLine("Значение добавлено!");
                Thread.Sleep(400);
                Console.Clear();
                goto start;
            }
            if (i == 3)
            {
                Console.Clear();
                var head="";
                if (d == 0) head = stack.Pop();
                else if (d == 1) head = stack_copy.Pop();
                Console.WriteLine("Извелеченное значение с вершины стека: {0}", head);
                Console.WriteLine("Нажмите ENTER для продолжения");
                Console.ReadLine();
                Console.Clear();
                goto start;
            }
            if (i == 4)
            {
                Console.Clear();
                var head = "";
                if (d == 0) head = stack.PopLast();
                else if (d == 1) head = stack_copy.PopLast();
                Console.WriteLine("Извелеченное значение из начала очереди: {0}", head);
                Console.WriteLine("Нажмите ENTER для продолжения");
                Console.ReadLine();
                Console.Clear();
                goto start;
            }
            if (i == 5)
            {
                Console.Clear();
                if (d == 0) stack.Remove();
                else if (d == 1) stack_copy.Remove();
                Console.WriteLine("Освобождение памяти от структуры данных!");
                Thread.Sleep(400);
                Console.Clear();
                goto start;
            }
            if (i == 6)
            {
                Console.Clear();
                Console.WriteLine("Клонирование стека!");
                stack_copy = stack.Clone();
                Thread.Sleep(400);
                Console.Clear();
                goto start;
            }
            if (i == 7)
                Console.Clear();
            {
                Console.Write("Выбор стека (0 - оригинал, 1 - копия): ");
                d = int.Parse(Console.ReadLine());
                if (d > 1)
                {
                    d = 0;
                }
                Thread.Sleep(400);
                Console.Clear();
                goto start;
            }
        }

    }

    public class Stack<T>
    {
        public T[] items;
        public int count;
        const int n = 1;
        public Stack()
        {
            items = new T[n];
        }

        public bool IsEmpty
        {
            get { return count == 0; }
        }
        public int Count
        {
            get { return count; }
        }

        public void Push(T item)
        {
            // увеличиваем стек
            if (count == items.Length)
                Resize(items.Length * 2);

            items[count++] = item;
        }
        public void PushLast(T item)
        {
            // увеличиваем стек
            if (count == items.Length)
                Resize(items.Length * 2);
            for (int i = count; i >= 0; i--)
            {
                if (i == 0)
                {
                    items[i] = item;
                }
                else
                {
                    items[i] = items[i - 1];
                }
            }
            count++;
        }
        public void List()
        {
            string[] res = new string[count];
            for (int i = 0; i < count; i++)
            {
                res[i] = items[i].ToString();
            }
            Console.WriteLine("{0}", string.Join(", ", res));
        }
        public T PopLast()
        {
            // если стек пуст, выбрасываем исключение
            if (IsEmpty)
                throw new InvalidOperationException("Стек пуст");
            T item = items[0];
            T[] tempItems = new T[items.Length * 2];
            for (int i = 1; i < count; i++)
            {
                tempItems[i-1]= items[i];
            }
            items = tempItems;
            count--;
            if (count > 0 && count < items.Length/2)
                Resize(items.Length/2);

            return item;
        }
        public T Pop()
        {
            // если стек пуст, выбрасываем исключение
            if (IsEmpty)
                throw new InvalidOperationException("Стек пуст");
            T item = items[--count];
            items[count] = default(T); // сбрасываем ссылку

            if (count > 0 && count < items.Length/2)
                Resize(items.Length/2);

            return item;
        }
        public bool Remove()
        {
            items = new T[n];
            count = 0;
            return true;
        }
        public T Peek()
        {
            return items[count - 1];
        }

        private void Resize(int max)
        {
            T[] tempItems = new T[max];
            for (int i = 0; i < count; i++)
                tempItems[i] = items[i];
            items = tempItems;
        }
        public Stack<T> Clone()
        {
            return new Stack<T> { items = this.items, count = this.count };
        }
    }
    class InvalidOperationException : Exception
    {
        public InvalidOperationException(string message) : base(message)
        {
            Console.Write(message);
        }
    }
}
