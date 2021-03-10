using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2_1_Stack
{
    
    class ArrayStack
    {
        
        int[] data;
        
        int top = -1;
        
        int size = 100;

        
        public ArrayStack()
        {
            data = new int[size];
        }


        public void Push(int el)
        {
            
            top++;
            
            if (top >= data.Length)
            {
                
                int[] data2 = new int[data.Length * 2];
                
                for (int i = 0; i < data.Length; i++)
                {
                    data2[i] = data[i];

                }
                
                this.data = data2;
            }
            
            data[top] = el;


        }

        public bool Pop(ref int r)
        {
            
            if (top < 0)
            {
                return false;
            }
            
            r = data[top];
            
            top--;
            return true;
        }


        public void Print()
        {
            
            for (int i = top; i >= 0; i--)
            {
                Console.WriteLine(data[i]);
            }
        }

        
        public int Size()
        {
            return top + 1;
        }

        
        public ArrayStack Clone()
        {
            var r = new ArrayStack();
            for (int i = 0; i <= top; i++)
            {
                r.Push(this.data[i]);
            }
            return r;
        }

    }

    class Program
    {
        static void Main(string[] args)
        {

            
            ArrayStack st = new ArrayStack();

            
            string ch = "";
            while (ch != "q")
            {
                Console.Clear();
                Console.WriteLine("[1] - Push");
                Console.WriteLine("[2] - Pop");
                Console.WriteLine("[3] - Print");
                Console.WriteLine("[4] - Size");
                Console.WriteLine("[q] - Выход");
                ch = Console.ReadLine();
                int y = 0;
                bool r = false;
                switch (ch)
                {
                    case "1":
                        Console.WriteLine("Введите значение для вставки в стек");
                        int x = Int32.Parse(Console.ReadLine());
                        st.Push(x);
                        break;
                    case "2":
                        {
                            r = st.Pop(ref y);
                            if (r)
                                Console.WriteLine("Результат операции Pop = " + y.ToString());
                            else
                                Console.WriteLine("Стек пустой");
                        }
                        break;
                    case "3":
                        Console.WriteLine("Содержимое стека");
                        st.Print();
                        break;
                    case "4":
                        Console.WriteLine("Размер стека = " + st.Size().ToString());
                        break;
                    default:
                        break;
                }
                Console.WriteLine("Нажмите любую кнопку для продолжения");
                Console.ReadKey();

            }
        }
    }
}
