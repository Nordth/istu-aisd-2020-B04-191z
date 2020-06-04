
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    int i, j, k, point1, point2, sum = 0, current_point, min_el, index_min_el, v_count, temp_sum, cities_count, min_sum;
    string min_route="", temp_str2, cities_str, unused_information, str, temp_str;
    

    /*    int roads[6][6] = {
        {0,10,17,9,0,0},
        {10,0,8,15,0,0},
        {17,8,0,10,7,0},
        {9,15,10,0,0,0},
        {0,0,7,0,0,8},
        {0,0,0,0,8,0}
        };*/
        //    char cities[6] = {'A','B','C','D','E','F'};

    
    ifstream infile("citymap.txt");

    i = 0;
    while (infile) {
        if (i == 1) {
            getline(infile, cities_str);
            break;
        }
        else {
            getline(infile, unused_information);
        }
        i++;
    }

    cities_count = (cities_str.length() / 2) + 1;

//    int v_sum[cities_count], v_visited[cities_count];
//    int roads[cities_count][cities_count];
    int *v_sum = new int[cities_count];
    int *v_visited = new int[cities_count];

    int** roads;
    roads = new int* [cities_count];
    for (i = 0; i < cities_count; i++) {
        roads[i] = new int[cities_count];
    }

    char* cities;
    cities = new char[cities_count];
    j = 0;
    for (i = 0; i < cities_str.length(); i++) {
        if ((cities_str[i] == ' ') || (cities_str[i] == '-') || (cities_str[i] == ',') || (cities_str[i] == '\n')) {
            continue;
        }
        else {
            cities[j] = cities_str[i];
            j++;
        }
    }

    if (j != cities_count) {
        cout << "SEPARATOR'S ERROR: list of cities in <citymap.txt> may be incorrect" << endl;
    }

    i = 0;
    while (infile) {
        if (i == 1) {
            for (k = 0; k < cities_count; k++) {
                for (j = 0; j < cities_count; j++) {
                    infile >> roads[k][j];
//                    cout << roads[k][j];
                }
//                cout << endl;
            }
        }
        else {
            getline(infile, unused_information);
        }
        i++;
    }
    infile.close();

    cout << "Enter the city name where route start: ";
    char begin_city;
    cin >> begin_city;

    cout << "Enter another cities where the route will be" << endl;
    cout << "(Possible separators: <-> or <,>): ";


    cin >> str;

    j = 0;
    temp_str = "";
    for (i = 0; i < str.length(); i++) {
        if ((int(str[i]) == 32) || (int(str[i]) == 45) || (int(str[i]) == 44)) {
            continue;
        }
        else {
            temp_str += str[i];
            j++;
        }
    }
    str = temp_str;

    int route_length = str.length() + 1;
    int factorial = 1;
    for (i = 1; i <= route_length - 1; i++) {
        factorial = factorial * i;
    }

    string *route_lists;
    route_lists = new string[factorial];

    sort(str.begin(), str.end());
    i = 0;
    do {
        route_lists[i] = begin_city + str;
        i++;
    } while (next_permutation(str.begin(), str.end()));
    int combination_count = i;

    for (i = 0; i < combination_count; i++) {
        temp_str = "";
        for (j = 0; j < route_lists[i].length(); j++) {
//            cout << route_lists[i][j];
            temp_str += route_lists[i][j];
            if (j != route_lists[i].length() - 1) {
                for (k = 0; k < cities_count; k++) {
                    if (route_lists[i][j] == cities[k]) {
                        point1 = k;
                        break;
                    }
                }
                for (k = 0; k < cities_count; k++) {
                    if (route_lists[i][j + 1] == cities[k]) {
                        point2 = k;
                        break;
                    }
                }

                //                if(roads[point1][point2] != 0){
                //                    sum = sum + roads[point1][point2];
                //                } else {

                for (k = 0; k < cities_count; k++) {
                    v_sum[k] = 0;
                    v_visited[k] = 0;
                }
                v_count = 0;
                current_point = point1;

                while (v_count != cities_count) {
                    for (k = 0; k < cities_count; k++) {
                        if ((roads[current_point][k] != 0) && (v_visited[k] == 0) && (k != current_point)) {
                            if ((v_sum[k] > roads[current_point][k] + v_sum[current_point]) || (v_sum[k] == 0)) {
                                v_sum[k] = roads[current_point][k] + v_sum[current_point];
                            }
                        }
                    }

                    v_visited[current_point] = 1;
                    v_count++;
                    min_el = 99999;//!!!
                    for (k = 0; k < cities_count; k++) {
                        if ((v_sum[k] < min_el) && (v_visited[k] == 0) && (v_sum[k] != 0)) {
                            min_el = v_sum[k];
                            index_min_el = k;
                        }
                    }
                    current_point = index_min_el;
                }

                current_point = point2;
                temp_str2 = "";
                temp_sum = v_sum[current_point];
                while (temp_sum != 0) {
                    for (k = 0; k < cities_count; k++) {
                        if ((roads[k][current_point] != 0) && ((v_sum[current_point] - roads[k][current_point]) == v_sum[k])) {
                            temp_sum = temp_sum - roads[k][current_point];
                            current_point = k;
                            if (temp_sum == 0) {
                                continue;
                            }
                            else {
                                temp_str2 += cities[current_point];
                            }
                            break;
                        }
                    }
                }
                if (temp_sum == 0) {
                    sum = sum + v_sum[point2];
                    for (k = 0; k < temp_str2.length(); k++) {
                        temp_str += temp_str2[temp_str2.length()-1-k];
                    }
                    
                }
                //                }
            }
        }
        if (i == 0) {
            min_sum = sum;
            min_route = temp_str;
        }
        else if (min_sum > sum) {
            min_sum = sum;
            min_route = temp_str;
        }
//        cout << sum << endl;
        sum = 0;
        
    }
//    cout << min_sum << min_route << endl;
    cout << "The fastest route:" << endl;
    for (i = 0; i < min_route.length(); i++) {
        if ((begin_city == min_route[i]) && (i==0)) {
            cout << "Start city:"<< min_route[i] << " -> ";
            continue;
        }
        for (j = 0; j < str.length(); j++) {
            if (str[j] == min_route[i]) {
                cout << "route city:" << min_route[i];

                temp_str = "";
                for (k = 0; k < str.length(); k++) {
                    if (j == k) {
                        continue;
                    }
                    else {
                        temp_str += str[k];
                    }
                }
                str = temp_str;
                break;
            }
            else if (j == (str.length() - 1)) {
                cout << "tranzit city:" << min_route[i];
            }
            
        }
        if (i != (min_route.length() - 1)) {
            cout << " -> ";
        }
        else {
            cout << ".";
        }
    }
    cout << endl << "Length route = " << min_sum << endl;
    system("pause");
    return 0;
}