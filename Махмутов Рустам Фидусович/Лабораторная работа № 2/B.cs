using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2_2_List
{
    //элемент динамического списка
    class RoundElement
    {
        public int Data;
        //ссылка на следующий элемент
        public RoundElement Next;
    }
    //Класс динамического списка
    class RoundList
    {
        //Поле (перменная внутри класса) указатель на первый элемент списка
        RoundElement first;
        public RoundList()
        {
        }

        //метод для добавления в конец списка
        public bool Add(int data)
        {
            //если список пустой
            if (first == null)
            {
                first = new RoundElement() { Data = data };
                first.Next = first;
            }
            //иначе найти конец списка и добавить элемент
            else
            {
                RoundElement el = first;
                //в цикле ищем конец - (поледний элемент с циклическом списке указывает на первый элемент)
                while (el.Next != first)
                {
                    el = el.Next;
                }
                RoundElement eln = new RoundElement() { Data = data, Next = first };
                el.Next = eln;

            }
            return true;
        }

        //добавления по индексу
        public bool Add(int data, int index)
        {
            //индексация с нуля, для апользователя с 1
            index--;
            if (index < 0)
                return false;
            //частный слчай добавляем перед первым элементом, список не пустой

            if (first != null && index == 0)
            {
                RoundElement last = first.Next;
                while (last.Next != first)
                {
                    last = last.Next;
                }
                //Последний элемент тпепрь ссылается на добавленный элемент, а добавленный ссылается на бывший первый элемент
                last.Next = new RoundElement() { Data = data, Next = first };
                //назначаем джоьбавленный элемент первым
                first = last.Next;
                return true;
            }
            //частный случай - добавляем перед первым жлементом, а список пустой
            if (first == null && index == 0)
            {
                first = new RoundElement() { Data = data };
                first.Next = first;
                return true;
            }

            //Общий случвй
            //предыдущий перед искомым элементов
            RoundElement prev = first;
            //текущий (искомый элемент) 
            RoundElement el = first.Next;
            int i = 1;
            //пока не найден индекс и мы не пришли к последнему элементу (последний в циклическом списке ссылается на первый)
            while (i != index && el.Next != first)
            {
                el = el.Next;
                prev = prev.Next;
                i++;
            }
            if (i != index)
                return false;
            //создаем новый элемент
            RoundElement eln = new RoundElement() { Data = data, Next = el };
            //обновляемый ссылки (предыдущий перд искомым элементом теперь ссылается на новый элемент)
            prev.Next = eln;
            return true;
        }


        //удаление элемента по индексу
        public bool Delete(int index)
        {
            //индексация с нуля, для апользователя с 1
            index--;
            //проверка что индекс не отрицательный
            if (index < 0)
                return false;
            //проверка что список не пустой
            if (first == null)
            {
                return false;
            }
            else
            {
                //частный случай  - удаляется первый элемент
                if (index == 0)
                {
                    //если только 1 элемент  списке
                    if (first.Next == first)
                    {
                        first = null;
                    }
                    else
                    {
                        //иначе находим последний элемент и меняем ему ссылку на следующий за первым элементом
                        RoundElement el = first;
                        while (el.Next != first)
                        {
                            el = el.Next;
                        }
                        el.Next = first.Next;
                        //первый элемент = следующий за первым
                        first = first.Next;
                    }
                }
                else
                {
                    //общий случай
                    RoundElement el = first.Next;
                    //в этой переменной будет храниться ссылка на предыдущий элемент. она необходима чтобы обновиться связи после удаления
                    RoundElement prev = first;
                    int i = 1;
                    //поиск элемент по индекс по не пришли к концу списка
                    while (index != i && el.Next != first)
                    {
                        prev = prev.Next;
                        el = el.Next;
                        i++;
                    }
                    //если элемент с заданным индексом не найден
                    if (i != index)
                        return false;
                    //на удаляемый элемент не осталось ссылок. память очистится сборщиком мусора
                    prev.Next = el.Next;
                }

            }

            return true;
        }

        public bool Get(int ind, ref int v)
        {
            ind--;
            //проверка что список не пустой

            if (first == null)
            {
                Console.WriteLine("Список пустой");
                return false;
            }
            //проверка что индекс не отрицательный

            if (ind < 0)
            {
                return false;
            }

            RoundElement el = first;
            int i = 0;
            //ищем элемнт в заданным индексом пока не пришли к концу списка
            while (i != ind && el.Next != first)
            {
                el = el.Next;
                i++;
            }
            //если не нашли элемеент, то ворзвращаем false
            if (i != ind)
                return false;
            v = el.Data;
            return true;
        }


        public void Print()
        {
            if (first == null)
            {
                Console.WriteLine("Список пустой");
                return;
            }
            RoundElement el = first;
            //в цикле печать элементов на экран (как минимум 1 раз напечатается, ели в списке только 1 элемент)
            do
            {
                Console.Write(el.Data.ToString() + " ");
                el = el.Next;
            }
            while (el != first);
            Console.WriteLine(Environment.NewLine);
        }


    }
    class Program
    {
        static void Main(string[] args)
        {
            RoundList rl = new RoundList();


            //переменная для хранения команды пользователя
            string ch = "";
            while (ch != "q")
            {
                Console.Clear();
                Console.WriteLine("[1] - Добавить в конец списка");
                Console.WriteLine("[2] - Добавить перед элементом");
                Console.WriteLine("[3] - Печать");
                Console.WriteLine("[4] - Получить по индексу");
                Console.WriteLine("[5] - Удалить по индексу");
                Console.WriteLine("[q] - Выход");
                ch = Console.ReadLine();
                int x = 0;
                bool r = false;
                int ind = 0;
                try
                {
                    switch (ch)
                    {
                        case "1":

                            Console.WriteLine("Введите значение для вставки в в конец списка");
                            x = Int32.Parse(Console.ReadLine());
                            rl.Add(x);


                            break;
                        case "2":

                            Console.WriteLine("Введите индекс");
                            ind = Int32.Parse(Console.ReadLine());
                            Console.WriteLine("Введите значение");
                            x = Int32.Parse(Console.ReadLine());
                            rl.Add(x, ind);
                            break;
                        case "3":
                            Console.WriteLine("Содержимое списка");
                            rl.Print();
                            break;
                        case "4":
                            Console.WriteLine("Введите индекс");
                            ind = Int32.Parse(Console.ReadLine());
                            r = rl.Get(ind, ref x);
                            if (r)
                                Console.WriteLine("Значение элемента = " + x.ToString());
                            else
                                Console.WriteLine("Элемент не найден");
                            break;
                        case "5":
                            Console.WriteLine("Введите индекс");
                            ind = Int32.Parse(Console.ReadLine());
                            r = rl.Delete(ind);
                            if (r)
                                Console.WriteLine("Элемент удален");
                            else
                                Console.WriteLine("Элемент не найден");
                            break;
                        default:
                            break;
                    }
                }
                catch (Exception ex) { Console.WriteLine("Ошибка входных данных, {0}", ex.Message); }
                Console.WriteLine("Нажмите любую кнопку для продолжения");
                Console.ReadKey();

            }
        }
    }
}
