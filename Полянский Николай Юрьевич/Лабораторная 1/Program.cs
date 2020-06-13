using System;
using System.Collections.Generic;
using System.Linq;

namespace Сортировка
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Пузырьковая сортировка");

            List<int> queue = new List<int>();

            Console.WriteLine("Отдельно введите 10 элементов");

            for (int i = 0; i < 10; i++)
            {
                queue.Add(Convert.ToInt32(Console.ReadLine()));
            }

            Console.Write("Очередь до сортировки: ");
            printArray(queue);

            insert_sort(queue);

            Console.Write("Строй после сортировки: ");
            printArray(queue);

            Console.WriteLine("\nСортировка слиянием");

            List<int> secondQueue = new List<int>();

            Console.WriteLine("Отдельно введите 10 элементов");

            for (int i = 0; i < 10; i++)
            {
                secondQueue.Add(Convert.ToInt32(Console.ReadLine()));
            }

            Console.Write("Очередь до сортировки: ");
            printArray(secondQueue);

            int[] secondQueueArray = merge_sort(secondQueue.ToArray());

            Console.Write("Очередь после сортировки: ");
            printArray(secondQueueArray.ToList());
        }

        public static void printArray(List<int> queue)
        {
            for (int i = 0; i < queue.Count; i++)
            {
                if (i < queue.Count - 1)
                {
                    Console.Write(queue[i] + " ");
                }
                else
                {
                    Console.WriteLine(queue[i]);
                }
            }
        }

        public static void insert_sort(List<int> queue)
        {
            // проход k равен индексу начала неотсортированной части
            for (int k = 1; k < queue.Count; k++)
            {
                int val = queue[k]; // первый элемент сравниваемый по k
                int j = k - 1; // первый элемент отсортированной части

                while (j >= 0 && val < queue[j]) // проверяем элементы отсортированной части
                {
                    queue[j + 1] = queue[j]; // правый больший = левый эл. отсортированной части
                    j--; // двигаемся влево по отсортированной части
                }
                // после выхода из while j всегда меньше на 1
                queue[j + 1] = val; // достигли нужного места
            }
        }

        public static int[] merge_sort(int[] arr)
        {
            if (arr.Length == 1)
            {
                return arr;
            }

            int middle = arr.Length / 2;

            int[] left = arr.Take(middle).ToArray();
            int[] right = arr.Skip(middle).ToArray();

            return merge(merge_sort(left), merge_sort(right));
        }

        public static int[] merge(int[] left, int[] right)
        {
            int size = left.Length + right.Length;

            int[] result = new int[size];

            int leftPointer = 0;
            int rightPointer = 0;

            for (int i = 0; i < size; i++)
            {
                if (leftPointer < left.Length && rightPointer < right.Length)
                {
                    if (left[leftPointer] > right[rightPointer])
                    {
                        result[i] = right[rightPointer];
                        rightPointer++;
                    }
                    else
                    {
                        result[i] = left[leftPointer];
                        leftPointer++;
                    }
                }
                else
                {
                    if (rightPointer < right.Length)
                    {
                        result[i] = right[rightPointer];
                        rightPointer++;
                    }
                    else
                    {
                        result[i] = left[leftPointer];
                        leftPointer++;
                    }
                }
            }

            return result;
        }
    }
}
