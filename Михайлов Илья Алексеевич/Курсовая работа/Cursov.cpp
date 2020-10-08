#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const int Size = 6;
bool boo = false;
int ob_dlina = 0;
int rast[2][Size];
int arr[Size][Size] = {
	{0, 10, 17, 9, 0, 0},
	{10, 0, 8, 15, 0, 0},
	{17, 8, 0, 10, 7, 0},
	{9, 15, 10, 0, 0, 0},
	{0, 0, 7, 0, 0, 8},
	{0, 0, 0, 0, 8, 0},
};

int Boolen(int);
void Gorod(int, vector<int>&, vector<string>&);
void Rast_do_Gorod(vector<int>&, int);
void Rast_min_put(vector<int>&, vector<string>&, int);
void Vivod(vector<int>&, vector<string>&, int);
void Vivod2();

void Vivod2()
{
	cout << "Весь пройденный путь равен: " << ob_dlina << endl;
}

void Vivod(vector<int>& rast_end, vector<string>& str, int dlina)
{
	ob_dlina += dlina;
	cout << "Вывод кратчайшего пути" << endl;
	for (int i = rast_end.size() - 1; i >= 0; i--)
	{
		cout << str[rast_end[i] - 1] << ", ";
	}
	cout << endl;
	cout << "Пройденный путь равен: " << dlina << endl;
}

void Rast_min_put(vector<int>& Kol, vector<string>& str, int end)
{
	vector <int> rast_end;
	int dlina = 0;
	int versh_end = Kol[end];
	rast_end.push_back(versh_end + 1);
	int vist = rast[1][versh_end];
	while (vist != 0)
	{
		for (int i = 0; i < Size; i++)
			if (arr[i][versh_end] != 0)
			{
				int temp = vist - arr[i][versh_end];
				if (temp == rast[1][i])
				{
					dlina += arr[i][versh_end];
					vist = temp;
					versh_end = i;
					rast_end.push_back(i + 1);
				}
			}
	}
	Vivod(rast_end, str, dlina);
}

void Rast_do_Gorod(vector<int>& Kol, int begin)
{
	int temp;
	for (int i = 0; i < Size; i++)
	{
		rast[0][i] = 1; //посещенные вершины
		rast[1][i] = -1; // Минимальное расстояние
	}
	rast[1][Kol[begin]] = 0; //Исправить на цикл
	for (int k = 0; k < Size; k++)
	{
		int i = 0;
		for (; i < Size; i++)
		{
			if (rast[0][i] == 1 && rast[1][i] != -1)
			{
				break;
			}
		}
		for (int j = 0; j < Size; j++)
		{
			if (arr[i][j] > 0)
			{
				temp = rast[1][i] + arr[i][j];
				if (rast[1][j] == -1)
				{
					rast[1][j] = temp;
				}
				else if (temp < rast[1][j])
				{
					rast[1][j] = temp;
				}
			}
		}
		rast[0][i] = 0;
	}
}

int Boolen(int start)
{
	if (boo == false)
	{
		cout << "Такого города нет!(попробуйте еще раз)" << endl;
		start++;
		return start;
	}
	return start;
}

void Gorod(int start, vector<int>& Kol, vector<string>& str)
{
	string slovo;
	int i = 0;
	for (; i < start; i++)
	{
		cout << "Введите название города: ";
		cin >> slovo;
		boo = false;
		for (int j = 0; j < Size; j++)
		{
			if (slovo == str[j])
			{
				boo = true;
				Kol.push_back(j);
				break;
			}
		}
		start = Boolen(start);
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	vector <string> str(Size); str = { "Moskva", "Kazan", "Perm", "Izhevsk", "Piter", "Votkinsk" };
	vector <int> Kol;
	int start;
	int begin, end;
	cout << "Города: ";
	for (int i = 0; i < Size; i++)
	{
		cout << str[i] << ", ";
	}
	cout << endl;
	cout << "Сколько городов пройти: ";
	cin >> start;
	Gorod(start, Kol, str);
	for (int i = 0; i < start - 1; i++)
	{
		begin = i;
		end = i + 1;
		Rast_do_Gorod(Kol, begin);
		Rast_min_put(Kol, str, end);
	}
	Vivod2();
	return 0;
}


