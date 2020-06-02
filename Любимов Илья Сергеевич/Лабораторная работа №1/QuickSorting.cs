using System;
namespace QuickSorting
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите элементы массива через пробелы: ");
            string read_arr = Console.ReadLine().Trim(' ');
            string[] arr = read_arr.Split(' ');
            // string[] arr = new string[7] { "4", "1", "6", "2", "1", "3", "5" };
            Console.WriteLine("Входной массив: {0}", string.Join(", ", arr));
            QuickSorting(arr, 0, arr.Length-1);
            Console.WriteLine("Результат быстрой сортирвки: {0}", string.Join(", ", arr));
            Console.ReadLine();
        }
        public static void QuickSorting(string[] arr, int first, int last)
        {
            int key = (last - first) / 2 + first, key_left = first, key_right = key + 1;
            int i = first, j = last;
            string buf;
            while (i<=j)
            {
                while (int.Parse(arr[i]) < int.Parse(arr[key]) && i <= last) ++i;
                while (int.Parse(arr[j]) > int.Parse(arr[key]) && j >= first) --j;
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
