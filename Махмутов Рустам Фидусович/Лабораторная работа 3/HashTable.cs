using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HashTable
{

    class HashTable
    {
        private int tableSize;
        private chainItem[] table;
        class chainItem
        {
            public int Key;
            public string Value;
            public chainItem Next = null;

        }
        public HashTable(int tableSize)
        {
            this.tableSize = tableSize;
            table = new chainItem[this.tableSize];

        }

        private int hash(int key)
        {
            return key % tableSize;
        }

        public bool addValue(int key, string val)
        {
            int hv = hash(key);
            var item = this.table[hv];

            if (item == null)
            {
                this.table[hv] = new chainItem();
                this.table[hv].Key = key;
                this.table[hv].Value = val;
                return true;
            }
            chainItem prev = null;
            while (item != null)
            {
                if (item.Key == key)
                    break;
                prev = item;
                item = item.Next;
            }

            if (item != null)
            {
                return false;
            }
            else
            {

                var tmp = new chainItem();
                prev.Next = tmp;
                tmp.Key = key;
                tmp.Value = val;
            }
            return true;

        }


        public bool setValue(int key, string val)
        {

            int hv = hash(key);

            var item = this.table[hv];

            if (item == null)
            {
                return false;
            }


            while (item != null)
            {
                if (item.Key == key)
                    break;
                item = item.Next;
            }

            if (item == null)
            {
                return false;
            }
            else
            {
                item.Value = val;
            }
            return true;

        }



        public bool cleanValue(int key)
        {

            int hv = hash(key);
  
            var item = this.table[hv];


            if (item == null)
            {
                return false;
            }


            chainItem prev = null;
            while (item != null)
            { 
               
                if (item.Key == key)
                    break;
                prev = item;
                item = item.Next;
            }

            if (item == null)
                return false;
            else
            {

                if (prev == null)
                {
                    this.table[hv] = item.Next;
                }
                else
                {
                    prev.Next = item.Next;
                }
            }
            return true;

        }

       
        public bool getValue(int key, ref string y)
        {
            
            var item = this.table[hash(key)];
            
            while (item != null)
            {
                if (item.Key == key)
                {
                    y = item.Value;
                    return true;
                }
                item = item.Next;
            }
            
            return false;
        }
    }
}
