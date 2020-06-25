using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.IO;
using System.Globalization;

namespace Курсовая
{
    class CustomCanvas : Panel
    {
        private List<DrawingVisual> visuals = new List<DrawingVisual>();

        private DrawingVisual myVisual = new DrawingVisual();

        public CustomCanvas(Point newPoint, string textPoint)
        {
            // Точка
            Draw(newPoint, textPoint);

            AddLogicalChild(myVisual);
            AddVisualChild(myVisual);

            visuals.Add(myVisual);
        }

        public CustomCanvas(Point pointOne, Point pointTwo, Point middlePoint, string text)
        {
            // Линия
            Draw(pointOne, pointTwo, middlePoint, text);

            AddLogicalChild(myVisual);
            AddVisualChild(myVisual);

            visuals.Add(myVisual);
        }

        // Точка
        public void Draw(Point point, string text)
        {
            DrawingContext myVisualContext = myVisual.RenderOpen();

            Pen ellipsePen = new Pen(Brushes.MediumTurquoise, 3);
            myVisualContext.DrawEllipse(ellipsePen.Brush, ellipsePen, point, 5, 5);

            string formattedTextPoint = ProcessingData.FromPointToString(point);

            FormattedText formattedText = new FormattedText(formattedTextPoint + "\n" + text, new CultureInfo("ru-RU"), FlowDirection.LeftToRight,
                new Typeface("Verdana"), 10, Brushes.Black, VisualTreeHelper.GetDpi(this).PixelsPerDip);

            Point formattedPoint = new Point(point.X, point.Y + 10);

            myVisualContext.DrawText(formattedText, formattedPoint);

            myVisualContext.Close();
        }

        // Линия
        public void Draw(Point pointOne, Point pointTwo, Point middlePoint, string text)
        {
            DrawingContext myVisualContext = myVisual.RenderOpen();

            Pen LinePen = new Pen(Brushes.Green, 2);
            myVisualContext.DrawLine(LinePen, pointOne, pointTwo);

            FormattedText formattedText = new FormattedText(text, new CultureInfo("ru-RU"), FlowDirection.LeftToRight,
                new Typeface("Verdana"), 10, Brushes.Black, VisualTreeHelper.GetDpi(this).PixelsPerDip);

            Point formattedPoint = new Point(middlePoint.X, middlePoint.Y - 10);

            myVisualContext.DrawText(formattedText, formattedPoint);

            myVisualContext.Close();
        }

        public static BitmapImage GetImage(byte[] imageArray)
        {
            var bytes = imageArray;

            var image = new BitmapImage();
            image.BeginInit();

            if (bytes == null)
            {
                // Processing null case
            }
            else
            {
                using (var ms = new MemoryStream(bytes))
                {
                    image.CacheOption = BitmapCacheOption.OnLoad;
                    image.StreamSource = ms;

                    image.EndInit();
                }
            }

            return image;
        }

        protected override Visual GetVisualChild(int index)
        {
            return visuals[index];
        }

        protected override int VisualChildrenCount
        {
            get { return visuals.Count; }
        }
    }
}
