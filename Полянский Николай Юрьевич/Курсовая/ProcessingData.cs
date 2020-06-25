using System;
using System.Windows;
using System.Collections.Generic;
using System.Text;
using System.Text.Unicode;
using System.Windows.Input;
using System.Xml;
using System.Windows.Controls;
using System.Xml.Linq;
using System.IO;
using System.Linq;
using System.Xml.XPath;
using System.Runtime.Intrinsics.X86;
using System.Threading;

namespace Курсовая
{
    class ProcessingData
    {
        public static void UnloadToXML(TownList<Point, string> townList)
        {
            var xmlDoc = new XDocument(new XDeclaration("1.0", "utf-8", "yes"),
                new XElement("Towns"));

            for (int i = 0; i < townList.Count; i++)
            {
                InsideDataTown<Point, string> town = townList.GetObject(i);

                xmlDoc.Root.Add(new XElement("Town", new XAttribute("id", i),
                    new XElement("Name", town.Name),
                    new XElement("Point", town.TownPoint)));
            }

            xmlDoc.Save(Path.Combine(Environment.CurrentDirectory, "townsMap.xml"));
        }

        public static (TownList<Point, string>, int) UploadFromXML()
        {
            var xmlDoc = XDocument.Load(Path.Combine(Environment.CurrentDirectory, "townsMap.xml"));

            TownList<Point, string> ddd = new TownList<Point, string>();

            var town = from xe in xmlDoc.Element("Towns").Elements("Town")
                        select new TempXMLData()
                        {
                            tempName = xe.Element("Name").Value,
                            tempPoint = xe.Element("Point").Value
                        };

            var futureTownList = town.ToList();

            TownList<Point, string> newTownList = new TownList<Point, string>();
            int count = 0;

            foreach (TempXMLData data in futureTownList)
            {
                newTownList.Add(FromStringToPoint(data.tempPoint), data.tempName);

                // В обход интерфейсов IEnumerable и IComparable для перебора готового объекта
                count++;
            }

            var resultTuple = (newTownList, count);

            return resultTuple;
        }

        public static string FromPointToString(Point pt)
        {
            return string.Format($"({pt.X}; {pt.Y})");
        }

        public static Point FromStringToPoint(string str)
        {
            string[] parts = str.Split(';');
            return new Point(double.Parse(parts[0]), double.Parse(parts[1]));
        }

        public static bool CheckCoordsPoint(Point checkPt, Point byPt)
        {
            if (Math.Abs(checkPt.X - byPt.X) <= 10 && Math.Abs(checkPt.Y - byPt.Y) <= 10)
            {
                // Входит в границы
                return true;
            }
            else
            {
                return false;
            }
        }

        public static double GetRangeByPoints(Point pt1, Point pt2)
        {
            double AB = Math.Sqrt(Math.Pow(pt1.X - pt2.X, 2) + Math.Pow(pt1.Y - pt2.Y, 2));

            return AB;
        }

        public static Point GetMiddlePointByTwo(Point pt1, Point pt2)
        {
            double X, Y, differenceX, differenceY;

            if (pt1.X > pt2.X)
            {
                differenceX = pt1.X - pt2.X;
                X = pt2.X + differenceX;
            }
            else if (pt1.X == pt2.X)
            {
                X = pt1.X;
            }
            else
            {
                differenceX = pt2.X - pt1.X;
                X = pt1.X + differenceX;
            }

            if (pt1.Y > pt2.Y)
            {
                differenceY = pt1.Y - pt2.Y;
                Y = pt2.Y + differenceY;
            }
            else if (pt1.Y == pt2.Y)
            {
                Y = pt1.Y;
            }
            else
            {
                differenceY = pt2.Y - pt1.Y;
                Y = pt1.Y + differenceY;
            }
            
            Point rangePoint = new Point(X, Y);

            return rangePoint;
        }

        public static void SetWay(Point pt, out string lastActionText, Canvas theCanvas)
        {
            Way map = Way.getObj();

            object townName = GetTown(pt, "str");
            //object townObj = GetTown(pt, "obj");

            lastActionText = "";

            if (map.PutRoad == true)
            {
                if (map.StartPoint is null)
                {
                    map.StartPoint = new InsideDataTown<Point, string>(pt, townName.ToString());
                    lastActionText = "Начало маршрута " + townName;
                }
                else if (map.EndPoint is null)
                {
                    map.EndPoint = new InsideDataTown<Point, string>(pt, townName.ToString());
                    lastActionText = "Конец маршрута " + townName;
                }
                else
                {
                    SetRange(map.StartPoint.TownPoint, map.EndPoint.TownPoint, theCanvas);
                    
                    map.StartPoint = null;
                    map.EndPoint = null;
                    
                    // Перерисовка точек
                    Points points = Points.getObj();
                    TownList<Point, string> towns = points.Towns; 

                    for (int i = 0; i < towns.Count; i++)
                    {
                        theCanvas.Children.Add(new CustomCanvas(towns.GetObject(i).TownPoint, towns.GetObject(i).Name));
                    }
                }
            }
            else
            {
                lastActionText = "Определен город " + townName;
            }
        }

        public static void SetRange(Point pt1, Point pt2, Canvas theCanvas)
        {
            (string, Point) result = GetRange(pt1, pt2);

            Way ways = Way.getObj();
            ways.CompleteMatrixWays(pt1, pt2, result.Item1);

            theCanvas.Children.Clear();

            theCanvas.Children.Add(new CustomCanvas(pt1, pt2, result.Item2, result.Item1));
        
        }

        public static (string, Point) GetRange(Point pt1, Point pt2)
        {
            string rangeString = GetRangeByPoints(pt1, pt2).ToString();

            Point rangePoint = GetMiddlePointByTwo(pt1, pt2);

            return (rangeString, rangePoint);
        }

        // Выбор можно структурой
        public static object GetTown(Point pt, string stroke)
        {
            Points points = Points.getObj();
            TownList<Point, string> checkedTowns = points.Towns;

            double tempRange, minRange = GetRangeByPoints(pt, checkedTowns.GetObject(0).TownPoint);
            int minTownId = 0;

            for (int i = 1; i < checkedTowns.Count; i++)
            {
                if (CheckCoordsPoint(pt, checkedTowns.GetObject(i).TownPoint))
                {
                    tempRange = GetRangeByPoints(pt, checkedTowns.GetObject(i).TownPoint);

                    if (tempRange < minRange)
                    {
                        minRange = tempRange;
                        minTownId = i;

                        break;
                    }
                }
            }

            if (stroke == "str")
            {
                return checkedTowns.GetElementName(minTownId);
            }
            else if (stroke == "obj")
            {
                return checkedTowns.GetObject(minTownId);
            }
            else
            {
                return null;
            }
        }

    }
}
