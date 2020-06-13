using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Transactions;

namespace Структуры_данных
{
    internal class DoublyLinkedList<T> //: IEnumerable<T>
    {
        // Головной и последний элемент
        DoublyNode<T> head;
        DoublyNode<T> tail;

        // Количество элементов списка
        int count;

        // Процедура добавления элемента в конец списка
        public void Add(T data)
        {
            // Инициализация нового элемента
            DoublyNode<T> node = new DoublyNode<T>(data);

            if (head == null)
            {
                head = node;
            }
            // Установка ссылки на следующий и предыдущий элемент
            else
            {
                tail.Next = node;
                node.Previous = tail;
            }

            // Установка конечного элемента
            tail = node;
            count++;
        }

        public void AddBefore(T data, int indexFind)
        {
            DoublyNode<T> node = new DoublyNode<T>(data);

            DoublyNode<T> current = GetObject(indexFind);
            DoublyNode<T> currentMinus = current.Previous;

            // связываем index - 1 и index со вставляемым элементом node и node с этими элементами
            // current = index
            current.Previous = node;

            // current = index - 1
            currentMinus.Next = node;

            node.Next = current;
            node.Previous = currentMinus;

            count++;
        }

        public void Print()
        {
            DoublyNode<T> current = head;

            // Вывод до tail
            while (current != tail)
            {
                Console.WriteLine(current.Data);
                current = current.Next;
            }

            // Вывод tail
            Console.WriteLine(current.Data);
        }

        private DoublyNode<T> GetObject(int indexFind)
        {
            if (head != null)
            {
                // Установка текущей головной позиции
                DoublyNode<T> current = head;

                int index = 0;

                while (current.Next != null && index != indexFind)
                {
                    current = current.Next;
                    index++;
                }

                return current;
            }
            else
            {
                Console.WriteLine("Невозможно найти элемент по индексу. Список пуст.");
                return null;
            }
        }

        public T GetElement(int index)
        {
            DoublyNode<T> element = GetObject(index);

            return element.Data;
        }

        public int GetRange(int indexFindOne, int indexFindTwo)
        {
            if (head != null)
            {
                DoublyNode<T> current = GetObject(indexFindOne);

                int index = indexFindOne;

                while (current.Next != null && index != indexFindTwo)
                {
                    current = current.Next;
                    index++;
                }

                return index - 1;
            }
            else
            {
                Console.WriteLine("Список пуст.");
                return 0;
            }
        }

        public bool Remove(T data)
        {
            DoublyNode<T> current = head;
            DoublyNode<T> previous = null;

            while (current != null)
            {
                if (current.Data.Equals(data))
                {
                    // Проверка на наличие элемента в середине
                    if (previous != null)
                    {
                        previous.Next = current.Next;
                        if (current.Next == null)
                        {
                            tail = previous;
                        }
                    }
                    else
                    {
                        head = head.Next;

                        if (head == null)
                        {
                            tail = null;
                        }
                    }

                    count--;

                    return true;
                }

                previous = current;
                current = current.Next;
            }

            return false;
        }

        public void Clear()
        {
            head = null;
            tail = null;
            count = 0;
        }

        //// Реализация интерфейса IEnumerable для возможности перебора списка циклом foreach
        //IEnumerator IEnumerable.GetEnumerator()
        //{
        //    return ((IEnumerable)this).GetEnumerator();
        //}

        //IEnumerator<T> IEnumerable<T>.GetEnumerator()
        //{
        //    DoublyNode<T> current = head;
        //    while (current != null)
        //    {
        //        yield return current.Data;
        //        current = current.Next;
        //    }
        //}
    }
}
