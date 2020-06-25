using System;
using System.Windows;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Курсовая
{
    public class TownList<Pt, St>
    {
        InsideDataTown<Point, string> head;
        InsideDataTown<Point, string> tail;

        public int Count { get; set; }

        public void Add(Point data, string name)
        {
            InsideDataTown<Point, string> newTown = new InsideDataTown<Point, string>(data, name);

            if (head == null)
            {
                head = newTown;
            }
            else
            {
                tail.Next = newTown ;
            }

            tail = newTown;

            Count++;
        }

        public string GetElementName(int index)
        {
            InsideDataTown<Point, string> element = GetObject(index);

            return element.Name;
        }

        internal InsideDataTown<Point, string> GetObject(int indexFind)
        {
            if (head != null)
            {
                InsideDataTown<Point, string> current = head;

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

        public int GetIndex(Point pt)
        {
            if (head != null)
            {
                InsideDataTown<Point, string> current = head;

                int index = 0;

                while (current != null && current != ProcessingData.GetTown(pt, "obj"))
                {
                    current = current.Next;
                    index++;
                }

                return index;
            }
            else
            {
                return 0;
            }
        }
    }
}
