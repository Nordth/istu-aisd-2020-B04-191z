using System;
using System.Windows;
using System.Collections.Generic;
using System.Text;
using System.Configuration;
using System.Dynamic;

namespace Курсовая
{
    class Way
    {
        public bool PutRoad { get; set; }
        public InsideDataTown<Point, string> StartPoint { get; set; }
        public InsideDataTown<Point, string> EndPoint { get; set; }

        public static int countTowns = Points.getObj().Towns.Count;

        public static string[,] Ways { get; set; }

        private static Way obj;

        private Way()
        {
            Ways = new string[countTowns, countTowns];
        }

        public static Way getObj()
        {
            if (obj is null)
            {
                obj = new Way();
            }

            return obj;
        }

        public void CompleteMatrixWays(Point pt1, Point pt2, string val)
        {
            TownList<Point, string> towns = Points.getObj().Towns;

            int indexOne = towns.GetIndex(pt1);
            int indexTwo = towns.GetIndex(pt2);

            for (int i = 0; i < countTowns; i++)
            {
                for (int j = 0; j < countTowns; j++)
                {
                    if (i == indexOne && j == indexTwo)
                    {
                        Ways[i, j] = val;
                    }
                }
            }
        }
    }
}
