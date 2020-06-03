using System;
namespace QuickSorting
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите элементы массива через пробелы: ");
            string read_arr = Console.ReadLine();
            string[] string_arr = read_arr.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            int[] arr = Array.ConvertAll(string_arr, int.Parse);
            Console.WriteLine("Входной массив: {0}", string.Join(", ", arr));
            QuickSorting(arr, 0, arr.Length - 1);
            Console.WriteLine("Результат быстрой сортирвки: {0}", string.Join(", ", arr));
            Console.ReadLine();
        }
        public static void QuickSorting(int[] arr, int first, int last)
        {
            int key = (last - first) / 2 + first, key_left = first, key_right = key + 1;
            int i = first, j = last, buf;
            while (i <= j)
            {
                while (arr[i] < arr[key] && i <= last) ++i;
                while (arr[j] > arr[key] && j >= first) --j;
                if (i <= j)
                {
                    buf = arr[i];
                    arr[i] = arr[j];
                    arr[j] = buf;
                    ++i; --j;
                }
            }
            if (j > first) QuickSorting(arr, first, j);
            if (i < last) QuickSorting(arr, i, last);
        }
    }
}
