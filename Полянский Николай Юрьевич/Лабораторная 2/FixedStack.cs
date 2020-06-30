using System;
using System.Collections.Generic;
using System.Text;

namespace Примеры
{
    class FixedStack<T>
    {
        private T[] items;
        private int count;

        public FixedStack(int n)
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
            {
                Resize(items.Length + 10);
            }

            items[count++] = item;
        }
        public T Pop()
        {
            // если стек пуст, выбрасываем исключение
            if (IsEmpty)
            {
                throw new InvalidOperationException("Стек пуст");
            }

            T item = items[--count];
            items[count] = default(T); // сбрасываем ссылку

            if (count > 0 && count < items.Length * 2)
            {
                Resize(items.Length * 2);
            }

            return item;
        }
        public T Peek()
        {
            return items[count - 1];
        }

        private void Resize(int max)
        {
            T[] tempItems = new T[max];

            for (int i = 0; i < count; i++)
            {
                tempItems[i] = items[i];
            }

            items = tempItems;
        }

        public FixedStack<T> Copy(FixedStack<T> newStack)
        {
            newStack.items = items;

            return newStack;
        }
    }
}
