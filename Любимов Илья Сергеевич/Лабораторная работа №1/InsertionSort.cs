using System;
namespace InsertionSort
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите элементы массива через пробелы: ");
            string read_arr = Console.ReadLine();
            string[] string_arr = read_arr.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            int[] arr = Array.ConvertAll(string_arr, int.Parse);
            Console.WriteLine("Массив до сортировки: {0}", string.Join(", ", arr));
            arr = InsertionSort(arr);
            Console.Write("Результат сортировки вставками: {0}", string.Join(", ", arr));
            Console.ReadLine();
        }
        public static int[] InsertionSort(int[] arr)
        {
            int length = arr.Length;
            int byf;
            for (var i = 0; i < length; i++)
            {
                int key = arr[i];
                int j = i;
                while ((j > 0) && (arr[j - 1] > key))
                {
                    byf = arr[j - 1];
                    arr[j - 1] = arr[j];
                    arr[j] = byf;
                    j--;
                }
                arr[j] = key;
            }
            return arr;
        }
    }
}
