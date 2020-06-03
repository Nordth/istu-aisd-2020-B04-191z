using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

namespace UnidirectionalLoopList
{
    class Program
    {
        static void Main(string[] args)
        {
            UnidirectionalLoopList<string> circularList = new UnidirectionalLoopList<string>();
            int i;
            bool flag = true;
            var res = true;
            while (flag)
            {
                Console.WriteLine("============Содержание============");
                if (circularList.Count == 0)
                {
                    Console.WriteLine("Пусто");
                }
                else
                {
                    Console.WriteLine("{0}", string.Join(", ", circularList));
                }
                Console.WriteLine("==================================");
                Console.WriteLine("Выберите действие:");
                Console.WriteLine("1.Вставка элемента в конец.");
                Console.WriteLine("2.Удаление элемента по значению.");
                Console.WriteLine("3.Получение значения элемента по индексу.");
                Console.WriteLine("4.Вставка элемента перед заданным индексом.");
                Console.WriteLine("5.Освобождение памяти от структуры данных.");
                Console.WriteLine("6.Текст.");
                Console.WriteLine("7.Выход.");
                Console.Write("Введите номер действия: ");
                i = int.Parse(Console.ReadLine());
                switch (i)
                {
                    case 1:
                        Console.Clear();
                        Console.Write("Введите значение: ");
                        circularList.Add(Console.ReadLine());
                        Console.WriteLine("Значение добавлено!");
                        Thread.Sleep(400);
                        Console.Clear();
                        break;
                    case 2:
                        Console.Clear();
                        Console.Write("Введите значение: ");
                        res = circularList.Remove(Console.ReadLine());
                        if (res == true)
                        {
                            Console.WriteLine("Значение удалено!");
                        }
                        else
                        {
                            Console.WriteLine("Значение не найдено!");
                        }
                        Thread.Sleep(400);
                        Console.Clear();
                        break;
                    case 3:
                        Console.Clear();
                        Console.Write("Введите индекс: ");
                        int w = int.Parse(Console.ReadLine());
                        res = circularList.Contains(w);
                        if (res == false) Console.WriteLine("Значение не найдено!");
                        Thread.Sleep(1000);
                        Console.Clear();
                        break;
                    case 4:
                        Console.Clear();
                        Console.Write("Введите индекс: ");
                        int serach = int.Parse(Console.ReadLine());
                        Console.Write("Введите добавляемое значение: ");
                        var add = Console.ReadLine();
                        res = circularList.AddBeforIndex(add, serach);
                        if (res == true)
                        {
                            Console.WriteLine("Значение добавленно!");
                        }
                        else
                        {
                            Console.WriteLine("Значение не найдено!");
                        }
                        Thread.Sleep(400);
                        Console.Clear();
                        break;
                    case 5:
                        Console.Clear();
                        Console.WriteLine("Освобождение памяти от структуры данных!");
                        Thread.Sleep(1000);
                        circularList.Clear();
                        Console.Clear();
                        break;
                    case 6:
                        Console.Clear();
                        Console.WriteLine("Вставка элемента в конец");
                        Console.WriteLine("Добавляем 12312");
                        circularList.Add("12312");
                        Console.WriteLine("{0}", string.Join(", ", circularList));
                        Console.WriteLine("Добавляем 5324");
                        circularList.Add("5324");
                        Console.WriteLine("{0}", string.Join(", ", circularList));
                        Console.WriteLine("Вставка элемента перед заданным индексом");
                        Console.WriteLine("Вставляем 111111 перед 2 индексом");
                        Console.WriteLine("{0}", string.Join(", ", circularList));
                        circularList.AddBeforIndex("111111", 2);
                        Console.WriteLine("{0}", string.Join(", ", circularList));
                        Console.WriteLine("Получение значения элемента по индексу");
                        Console.WriteLine("Получаем элемент с индексом 2");
                        circularList.Contains(2);
                        Console.WriteLine("Удаление элемента по значению");
                        Console.WriteLine("Удаляем 12312");
                        Console.WriteLine("{0}", string.Join(", ", circularList));
                        circularList.Remove("12312");
                        Console.WriteLine("{0}", string.Join(", ", circularList));
                        circularList.Clear();
                        Console.WriteLine("Нажмите Enter для продолжения");
                        Console.ReadLine();
                        Console.Clear();
                        break;
                    case 7:
                        flag = false;
                        break;
                    default:
                        Console.Clear();
                        Console.WriteLine("Неизвестное действие!");
                        Thread.Sleep(400);
                        Console.Clear();
                        break;
                }         
            }  
        }
    }

    class UnidirectionalLoopList<T> : IEnumerable<T>
    {

        Node<T> head; // головной/первый элемент
        Node<T> tail; // последний/хвостовой элемент
        int count;  // количество элементов в списке

        public bool IsEmpty { get { return count == 0; } }
        public int Count { get { return count; } }

        /// <summary>
        /// Добавление элмента
        /// </summary>
        /// <param name="data"></param>
        public void Add(T data)
        {
            Node<T> node = new Node<T>(data);
            // если список пуст
            if (head == null)
            {
                head = node;
                tail = node;
                tail.Next = head;
            }
            else
            {
                node.Next = head;
                tail.Next = node;
                tail = node;
            }
            count++;
        }
        /// <summary>
        /// Вставка элемента перед заданным индексом
        /// </summary>
        /// <param name="data">Что вставать</param>
        /// <param name="search"> перед чем вставить</param>
        public bool AddBeforIndex(T data, int search)
        {
            Node<T> node = new Node<T>(data);
            int op = 0;
            int p = 1;
            // если список пуст
            if (head == null)
            {
                head = node;// головной/первый элемент
                tail = node;// последний/хвостовой элемент
                tail.Next = head;
            }
            else
            {
                Node<T> current = head;
                do
                {
                    if (p == search)
                    {
                        if (current.Data.Equals(head.Data))
                        {
                            //Console.WriteLine("HEAD");
                            Node<T> node_buf = head;
                            head = node;
                            head.Next = node_buf;
                            tail.Next = head;
                            node_buf.Next = current.Next;
                            op = 1;
                            break;
                        }
                        Node<T> current_out = head;
                        do
                        {
                            if (current_out.Next.Data.Equals(current.Data))
                            {
                                //node.Next = current;
                                //tail.Next = node;
                                //tail = node;
                                current_out.Next = node;
                                node.Next = current;
                                op = 1;
                                break;
                            }
                            current_out = current_out.Next;
                        }
                        while (current_out != head);
                        break;
                    }
                    p++;
                    current = current.Next;
                }
                while (current != head);
            }
            if (op == 1)
            {
                count++;
                return true;
            }
            else
            {
                return false;
            }
        }
        public bool Remove(T data)
        {
            Node<T> current = head;
            Node<T> previous = null;

            if (IsEmpty) return false;

            do
            {
                if (current.Data.Equals(data))
                {
                    // Если узел в середине или в конце
                    if (previous != null)
                    {
                        // убираем узел current, теперь previous ссылается не на current, а на current.Next
                        previous.Next = current.Next;

                        // Если узел последний,
                        // изменяем переменную tail
                        if (current == tail)
                            tail = previous;
                    }
                    else // если удаляется первый элемент
                    {

                        // если в списке всего один элемент
                        if (count == 1)
                        {
                            head = tail = null;
                        }
                        else
                        {
                            head = current.Next;
                            tail.Next = current.Next;
                        }
                    }
                    count--;
                    return true;
                }

                previous = current;
                current = current.Next;
            } while (current != head);

            return false;
        }

        public void Clear()
        {
            head = null;
            tail = null;
            count = 0;
        }

        public bool Contains(int k)
        {
            Node<T> current = head;
            int i = 1;
            if (current == null) return false;
            do
            {
                if (i == k)
                {
                    Console.WriteLine(current.Data);
                    return true;
                }
                i++;
                current = current.Next;
            }
            while (current != head);
            return false;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)this).GetEnumerator();
        }

        IEnumerator<T> IEnumerable<T>.GetEnumerator()
        {
            Node<T> current = head;
            do
            {
                if (current != null)
                {
                    yield return current.Data;
                    current = current.Next;
                }
            }
            while (current != head);
        }
    }

    public class Node<T>
    {
        public Node(T data)
        {
            Data = data;
        }
        public T Data { get; set; }
        public Node<T> Next { get; set; }
    }
}
