using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1_Sort
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Укажите размер массива");
            
            int size = Int32.Parse(Console.ReadLine());
            
            int[] data = new int[size];
            Console.WriteLine("Выберите способ ввода данных: 1 - генератор чисел, 2 - вручную");
            
            string ch = Console.ReadLine();
            
            if (ch == "1")
            {
                
                Random r = new Random(DateTime.Now.Millisecond);
                
                for (int i = 0; i < data.Length; i++)
                {
                    
                    data[i] = r.Next() % 100;
                    
                    Console.Write(string.Format("{0} ", data[i]));
                }
                Console.Write(Environment.NewLine);
            }
            else
            {
                
                for (int i = 0; i < data.Length; i++)
                {
                    Console.Write(string.Format("Введите элемент № {0} ", i + 1));
                    data[i] = Int32.Parse(Console.ReadLine());
                }
            }
            

            Console.WriteLine("Выберите способ сортировки: 1 - вставками, 2 - быстрая");
            
            ch = Console.ReadLine();
            
            if (ch == "1")
            {
                
                for (int i = 1; i < data.Length; i++)
                {
                    int tmp = data[i];
                    int j = i - 1;
                    
                    while (j > 0 && data[j] > data[i])
                    {
                        data[j + 1] = data[j];
                        j--;
                    }
                    data[j] = tmp;
                }
            }
            else
            {
                

                FastSort(data, 0, data.Length - 1);
            }

            Console.WriteLine("Отсортированный массив:");
            for (int i = 0; i < data.Length; i++)
            {
                Console.Write(string.Format("{0} ", data[i]));
            }
            Console.Write(Environment.NewLine);

            Console.WriteLine("Для завершения работы нажмите любую кнопку");
            Console.ReadKey();


        }

        
        private static void FastSort(int[] data, int a, int b)
        {
            
            int x = data[a];
            int a_old = a;
            int b_old = b;
            while (a < b)
            {
                
                while (data[b] >= x && a < b)
                {
                    b--;
                }
                
                if (a != b)
                {
                    data[a] = data[b];
                    a++;
                }
                

                while (data[a] <= x && a < b)
                {
                    a++;
                }
                
                if (a != b)
                {
                    data[b] = data[a];
                    b--;
                }
            }
            
            data[a] = x;
            
            if (a_old < a)
                FastSort(data, a_old, a - 1);
            if (b_old > a)
                FastSort(data, a + 1, b_old);
        }
    }
}
