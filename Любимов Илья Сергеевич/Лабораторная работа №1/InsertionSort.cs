using System;
namespace InsertionSort
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Введите элементы массива через пробелы: ");
            string read_arr = Console.ReadLine().Trim(' ');
            string[] arr = read_arr.Split(' ');
            arr = InsertionSort(arr);

            Console.Write("Результат сортировки вставками: {0}", string.Join(", ",arr));
            Console.ReadLine();
        }
        public static string[] InsertionSort(string[] arr)
        {
            int lenght = arr.Length;
            string byf;
            for (var i = 0; i < lenght; i++)
            {
                int key = int.Parse(arr[i]);
                int j = i;
                while ((j > 0) && (int.Parse(arr[j - 1]) > key))
                {
                    byf = arr[j - 1];
                    arr[j - 1] = arr[j];
                    arr[j] = byf;
                    j--;
                }
                arr[j] = key.ToString();
            }
            return arr;
        }
    }
}
