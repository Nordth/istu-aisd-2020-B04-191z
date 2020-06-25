using System;
using System.Windows;
using System.Collections.Generic;
using System.Text;

namespace Курсовая
{
    class Points
    {
        private static TownList<Point, string> towns;

        private static Points obj;

        private Points() { }

        public static Points getObj()
        {
            if (obj is null)
            {
                obj = new Points();
            }

            return obj;
        }

        public TownList<Point, string> Towns
        {
            get { return towns; }
            set { towns = value; }
        }
    }
}
