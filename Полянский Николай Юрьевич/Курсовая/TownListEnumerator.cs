using System;
using System.Windows;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Курсовая
{
    class TownListEnumerator : IEnumerator
    {
        TownList<Point, string> list;

        int position = -1;

        public TownListEnumerator(TownList<Point, string> townList)
        {
            list = townList;
        }

        public object Current
        {
            get
            {
                if (position == -1 || position >= list.Count)
                {
                    throw new InvalidOperationException();
                }

                return list.GetObject(position);
            }
        }

        public bool MoveNext()
        {
            if (position < list.Count - 1)
            {
                position++;
                return true;
            }
            else
                return false;
        }

        public void Reset()
        {
            position = -1;
        }
    }
}
