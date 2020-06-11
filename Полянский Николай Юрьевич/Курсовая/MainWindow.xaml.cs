using System;
using System.Windows;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml.Linq;

namespace Курсовая
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Upload_Map(object sender, RoutedEventArgs e)
        {
            (TownList<Point, string>, int) uploadedTowns = ProcessingData.UploadFromXML();

            int countTowns = uploadedTowns.Item2;

            MyCanvas.Children.Clear();

            Points points = Points.getObj();
            points.Towns = uploadedTowns.Item1;

            TownList<Point, string> checkedTowns = points.Towns;

            for (int i = 0; i < countTowns; i++)
            {
                MyCanvas.Children.Add(new CustomCanvas(checkedTowns.GetObject(i).TownPoint, checkedTowns.GetElementName(i)));
            }

            lastAction.Text = "Загружены города";
        }

        private void Unload_Map(object sender, RoutedEventArgs e)
        {
            Points asd = Points.getObj();
            ProcessingData.UnloadToXML(asd.Towns);

            lastAction.Text = "Выгружены города";
        }

        private void MyCanvas_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Canvas theCanvas = MyCanvas;
            ComplementList(sender, e, theCanvas);
        }

        private void putRoad_Click(object sender, RoutedEventArgs e)
        {
            Way map = Way.getObj();

            if (map.PutRoad == false)
            {
                map.PutRoad = true;
            }
            else
            {
                map.PutRoad = false;
            }
        }

        public void ComplementList(object sender, MouseButtonEventArgs e, Canvas theCanvas)
        {
            Point pt = e.GetPosition((UIElement)sender);

            HitTestResult hitResult = VisualTreeHelper.HitTest(MyCanvas, pt);

            DrawingVisual result = hitResult.VisualHit as DrawingVisual;

            if (result != null)
            {
                ProcessingData.SetWay(pt, out string lastActionText, theCanvas);
                lastAction.Text = lastActionText;
            }
            else
            {
                AddTown(pt, out string nameTown);
                lastAction.Text = "Добавлен город " + nameTown;
            }
        }


        public void AddTown(Point pt, out string nameTown)
        {
            Points points = Points.getObj();
            TownList<Point, string> pointsToTownList = points.Towns;

            nameTown = "Unknown";

            if (newTown.Text != "")
            {
                nameTown = newTown.Text;
            }

            if (pointsToTownList is null)
            {
                pointsToTownList = new TownList<Point, string>();
            }

            pointsToTownList.Add(pt, nameTown);
            points.Towns = pointsToTownList;

            MyCanvas.Children.Add(new CustomCanvas(pt, nameTown));

            lastAction.Text = "Добавлен город " + nameTown;
        }
    }
}
