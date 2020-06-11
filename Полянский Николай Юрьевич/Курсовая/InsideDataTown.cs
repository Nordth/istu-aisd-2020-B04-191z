using System;
using System.Windows;
using System.Collections.Generic;
using System.Text;

namespace Курсовая
{
    class InsideDataTown<Pt, St>
    {
        public InsideDataTown(Point point, string name)
        {
            TownPoint = point;
            Name = name;
        }

        public Point TownPoint { get; set; }
        public string Name { get; set; }
        public InsideDataTown<Point, string> Next { get; set; }
    }
}
