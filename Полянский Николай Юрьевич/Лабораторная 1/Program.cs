using System;
using System.Linq;

namespace Сортировка
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Пузырьковая сортировка");

            int[] A = new int[] { 175, 190, 174, 199, 180, 179, 181, 182, 189, 171 };

            Console.Write("Строй до сортировки: ");
            printArray(A);

            insert_sort(A);

            Console.Write("Строй после сортировки: ");
            printArray(A);

            Console.WriteLine("\nСортировка слиянием");

            int[] D = new int[] { 21, 6, 7, 2, 8, 25, 29, 11, 15, 16, 19, 22, 23, 12 };

            Console.Write("Очередь до сортировки: ");
            printArray(D);

            int[] newD = merge_sort(D);

            Console.Write("Очередь после сортировки: ");
            printArray(newD);
        }

        public static void printArray(int[] arr)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                if (i < arr.Length - 1)
                {
                    Console.Write(arr[i] + " ");
                }
                else
                {
                    Console.WriteLine(arr[i]);
                }
            }
        }

        public static void insert_sort(int[] arr)
        {
            // проход k равен индексу начала неотсортированной части
            for (int k = 1; k < arr.Length; k++)
            {
                int val = arr[k]; // первый элемент сравниваемый по k
                int j = k - 1; // первый элемент отсортированной части

                while (j >= 0 && val < arr[j]) // проверяем элементы отсортированной части
                {
                    arr[j + 1] = arr[j]; // правый больший = левый эл. отсортированной части
                    j--; // двигаемся влево по отсортированной части
                }
                // после выхода из while j всегда меньше на 1
                arr[j + 1] = val; // достигли нужного места
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
