#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

const int max_roads = 20;

struct City
{
	int ind;
	City* ptr;
	City** dir;
	int dist[max_roads];
	int buffer;
	char name;
	City(char a) {
		dir = new City*[max_roads];
		name = a;
		buffer = -1;
		ind = 0;
		ptr = nullptr;
	}
};

struct Map
{
	vector <City*> towns;
	Map() {
		towns = {};
	}
};

void clearroute(Map &a) { //clear all buffers where distances reseived
	for (int i = 0; i < a.towns.size(); i++) {
		a.towns[i]->buffer = -1;
	}
}

void settown(Map &m, char a, char b, int d) {//input new town in towns map 
	int ai = -1;
	int bi = -1;
	for (int i = 0; i < m.towns.size(); i++) {
		if (a == m.towns[i]->name) {
			ai = i;
		}
		if (b == m.towns[i]->name) {
			bi = i;
		}
	}
	if (ai == -1 && bi == -1) {
		City* A = new City(a);
		City* B = new City(b);
		A->ptr = A;
		B->ptr = B;
		A->dir[A->ind]=B;
		A->dist[A->ind]=d;
		A->ind++;
		B->dir[B->ind] = A;
		B->dist[B->ind] = d;
		B->ind++;
		m.towns.push_back(A);
		m.towns.push_back(B);
	}
	else if (ai == -1 && bi != -1) {
		City* A = new City(a);
		A->ptr = A;
		A->dir[A->ind] = m.towns[bi]->ptr;
		A->dist[A->ind]=d;
		A->ind++;
		m.towns[bi]->dir[m.towns[bi]->ind]=A;
		m.towns[bi]->dist[m.towns[bi]->ind]=d;
		m.towns[bi]->ind++;
		m.towns.push_back(A);
	}
	else if (ai != -1 && bi == -1) {
		City* B = new City(b);
		B->ptr = B;
		B->dir[B->ind] = m.towns[ai]->ptr;
		B->dist[B->ind] = d;
		B->ind++;
		m.towns[ai]->dir[m.towns[ai]->ind] = B;
		m.towns[ai]->dist[m.towns[ai]->ind] = d;
		m.towns[ai]->ind++;
		m.towns.push_back(B);
	}
	else {
		m.towns[bi]->dir[m.towns[bi]->ind]=m.towns[ai]->ptr;
		m.towns[bi]->dist[m.towns[bi]->ind]=d;
		m.towns[bi]->ind++;
		m.towns[ai]->dir[m.towns[ai]->ind] = m.towns[bi]->ptr;
		m.towns[ai]->dist[m.towns[ai]->ind] = d;
		m.towns[ai]->ind++;
	}
}

void marsh (Map &m, char A) { //shorter distance from A to all ander towns
	int j = -1;
	for (int i = 0; i < m.towns.size(); i++) {
		if (A == m.towns[i]->name) {
			j = i;
			break;
		}
	}
	m.towns[j]->buffer = 0;
	for (int z = 0; z < m.towns.size(); z++) {
		for (int i = 0; i < m.towns.size(); i++) {
			if (i != j) {
				int min = -1;
				int index=0;
				for (int k = 0; k < m.towns[i]->ind; k++) {
					if (m.towns[i]->dir[k]->buffer != -1) {
						index = k;
						min = m.towns[i]->dir[k]->buffer + m.towns[i]->dist[k];
						break;
					}
				}
				for (int k = index+1; k < m.towns[i]->ind; k++) {
					if (m.towns[i]->dir[k]->buffer != -1) {
						if (m.towns[i]->dir[k]->buffer + m.towns[i]->dist[k] < min) {
							min = m.towns[i]->dir[k]->buffer + m.towns[i]->dist[k];
						}
					}
				}
				if (min != -1 && m.towns[i]->buffer==-1) {
					m.towns[i]->buffer = min;
				}
				else if (min != -1 && m.towns[i]->buffer > min) {
					m.towns[i]->buffer = min;
				}
			}
		}
	}
}

void printTrack(Map &m, char A, char B) { //shorter track from A to B print
	vector <char> Names = {};
	Names.push_back(B);
	int end=-1;
	char title=B;
	for (int j = 0; j < m.towns.size(); j++) {
		for (int i = 0; i < m.towns.size(); i++) {
			if (m.towns[i]->name == title) {
				end = i;
				break;
			}
		}
		int min = 0;
		for (int i = 0; i < m.towns[end]->ind; i++) {
			if (m.towns[end]->buffer - m.towns[end]->dist[i] == m.towns[end]->dir[i]->buffer&&
				m.towns[end]->dir[i]->buffer != -1) {
				title = m.towns[end]->dir[i]->name;
				Names.push_back(title);
				break;
			}
		}
		if (title == A) break;
	}
	for (int i = Names.size() - 2; i > 0; i--) {
		cout << Names[i] << "   transit city\n";
	}
	cout << Names[0] << "   destination city\n";
}

void print_buffers(Map &a) {//output city buffer and exists dictances among cityes (for debugging)
	for (int i = 0; i < a.towns.size(); i++) {
		cout<< a.towns[i]->name<<' ' << a.towns[i]->buffer << '\n';
		for (int j = 0; j < a.towns[i]->ind; j++) {
			cout << a.towns[i]->ptr->name << ' ' << a.towns[i]->dir[j]->name
				<< ' ' << a.towns[i]->dist[j]<<'\n';
		}
	}
}

int main () {
	Map M = Map();
	vector<char> marshroute;
	char sit1, sit2;
	int distans;
	ifstream ist{ "example.txt" };
	ifstream run{ "run.txt" };
	while (ist>>sit1>>sit2>>distans)
	{
		settown(M, sit1, sit2, distans);
	}
	cout << "please input marshroute\n";
	while (cin >> sit1) {
		marshroute.push_back(sit1);
	}
	cout << marshroute[0] << "   starting city\n";
	for (int i = 0; i < marshroute.size() - 1; i++) {
		clearroute(M);
		marsh(M, marshroute[i]);
		printTrack(M, marshroute[i], marshroute[i + 1]);
	}
	print_buffers(M);
}