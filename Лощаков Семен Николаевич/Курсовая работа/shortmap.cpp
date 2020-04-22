/*Построение оптимального маршрута

На карте размещено несколько городов, связанных в виде графа.
Каждое ребро графа обозначает допустимость пути из одного
города в другой и содержит число – расстояние между городами.
Оператор вводит начальный город и список городов - адресатов.
Необходимо составить оптимальный маршрут(с минимальной длиной пути), 
стартующий от начального города и проходящий по всем городам - адресатам.
Маршрут должен быть представлен в виде списка городов в порядке их посещения, 
каждому из которых добавлен один из следующих признаков : начальный город, город - адресат, 
транзитный город(не является адресатом, либо повторный въезд в город - адресат).
Город может несколько раз присутствовать в списке, если этого требует оптимальный маршрут.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int numberCities(vector<string> a, string b) {
    int temp = 0;

    for (int i = 0; i < (int)a.size(); i++)
    {
        if (a[i] == b) return temp = i;
    }
    return temp;
}

const int n = 10; 
const int inf = 1000 * 1000 * 1000; 

int g[n][n] =
{
   {0, 20, 25, 30, 0, 0, 0, 0, 0, 0},
   {20, 0, 0, 5, 0, 10, 0, 0, 0, 0},
   {25, 0, 0, 0, 0, 10, 15, 0, 0, 0},
   {30, 5, 0, 0, 25, 0, 0, 0, 0, 0},
   {0, 0, 0, 25, 0, 15, 0, 5, 10, 20},
   {0, 10, 10, 0, 15, 0, 10, 0, 0, 0},
   {0, 0, 15, 0, 0, 10, 0, 15, 0, 0},
   {0, 0, 0, 0, 5, 0, 15, 0, 0, 10},
   {0, 0, 0, 0, 10, 0, 0, 0, 0, 10},
   {0, 0, 0, 0, 20, 0, 0, 10, 10, 0},
};

int main()
{
    setlocale(LC_ALL, "Rus");
    vector <string> cities(10);
    cities = { "Atlanta", "Boston", "Columbus", "Denver", "Eugene", "Fremont", "Gilbert", "Houston", "Irvine", "Jersey" };
    vector <int> d(n, inf), p(n, -1);
    vector <bool> used(n);
    string first, last; 

    cout << "Список городов: ";
    for (int i = 0; i < cities.size(); i++)
    {
        cout << cities[i] << " ";
    }

    cout << "\n\n" << "Выберите начало и конец маршрута: ";
    cin >> first >> last;

    int start = numberCities(cities, first), finish = numberCities(cities, last), mn, u;
    d[start] = 0;

    for (int i = 0; i < n; ++i) {
        mn = inf, u = -1;
        for (int j = 0; j < n; ++j)
            if (!used[j] && d[j] < mn)
                mn = d[j], u = j;
        if (u == -1)    break;
        used[u] = true;
        for (int j = 0; j < n; ++j)
            if (d[j] > d[u] + g[u][j] && g[u][j] > 0)
                d[j] = d[u] + g[u][j], p[j] = u;
    }

    cout << "Маршрут из " << cities[start] << " в " << cities[finish] << ": " << endl << endl;

    vector <int> v;
    if (p[finish] == -1)
        cout << "No way\n";
    else {
        for (int u = finish; u != -1; u = p[u])
            v.push_back(u);
        reverse(v.begin(), v.end());
        int size = v.size();
        cout << "Начальный город " << cities[v[0]] << endl;

        for (int i = 1; i < (int)v.size() - 1; ++i) {
            cout << "Транзитный город " << cities[v[i]] << endl;
        }
        cout << "Город-адресат " << cities[v[size - 1]] << endl;
    }

    cout << "\n" << "Путь равен: " << d[finish] << "\n";
}
