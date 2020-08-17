#include <iostream>
#include <algorithm>
#include <vector>

const int INF = 1e9 + 7;

void getShortestPath(int u, int v, std::vector<std::vector<int>>& distances, std::vector<std::vector<int>>& next, std::vector<int>& path)
{
	if (distances[u][v] == INF)
	{
		return;
	}
	int c = u;
	while (c != v)
	{
		path.push_back(c + 1);
		//std::cout << c + 1 << std::endl;
		c = next[c][v];
	}
	path.push_back(v + 1);
	//std::cout << v + 1 << std::endl;
}

void check(std::vector<int>& destination_ñities, std::vector<int>& best_permutation, std::vector<std::vector<int>>& distances, int& min_sum, int& start, int& num_of_destination_cities)
{
	int sum = 0;
	sum += distances[start][destination_ñities[0]];
	for (int i = 0; i < num_of_destination_cities - 1; ++i)
	{
		sum += distances[destination_ñities[i]][destination_ñities[i + 1]];
	}
	if (sum < min_sum)
	{
		min_sum = sum;
		best_permutation.clear();
		for (int i = 0; i < num_of_destination_cities; ++i)
		{
			best_permutation.push_back(destination_ñities[i]);
		}
	}
}

bool in(int a, std::vector<int>& vec)
{
	for (int i : vec)
	{
		if (i == a)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::cout << "Starting city:" << std::endl;
	int start;
	std::cin >> start;
	start--;
	std::cout << "Input the number of destination cities:" << std::endl;
	int num_of_destination_cities;
	std::cin >> num_of_destination_cities;
	std::cout << "Destination cities:" << std::endl;
	std::vector<int> destination_ñities;
	for (int i = 0; i < num_of_destination_cities; ++i)
	{
		int city;
		std::cin >> city;
		city--;
		destination_ñities.push_back(city);
	}
	/*for (int a : destination_ñities)
	{
		std::cout << a << ' ';
	}*/
	std::cout << "Input the number of all cities:" << std::endl;
	int n;
	std::cin >> n;
	std::cout << "Distances between cities in the form of a square matrix. If there is no way, input -1" << std::endl;
	std::vector<std::vector<int>> distances(n, std::vector<int>(n));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cin >> distances[i][j];
			if (distances[i][j] == -1)
			{
				distances[i][j] = INF;
			}
		}
	}
	std::vector<std::vector<int>> next(n, std::vector<int>(n));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (distances[i][j] == INF)
			{
				next[i][j] = -1;
			}
			else
			{
				next[i][j] = j;
			}
		}
	}
	/*for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << next[i][j] << ' ';
		}
		std::cout << std::endl;
	}*/
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (distances[i][k] + distances[k][j] < distances[i][j])
				{
					distances[i][j] = distances[i][k] + distances[k][j];
					next[i][j] = next[i][k];
				}
				//distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
			}
		}
	}
	/*for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << distances[i][j] << ' ';
		}
		std::cout << std::endl;
	}*/
	int min_sum = INF;
	std::vector<int> best_permutation;
	std::sort(destination_ñities.begin(), destination_ñities.end());
	check(destination_ñities, best_permutation, distances, min_sum, start, num_of_destination_cities);
	/*for (int city : destination_ñities)
	{
		std::cout << city << ' ';
	}
	std::cout << std::endl;*/
	while (std::next_permutation(destination_ñities.begin(), destination_ñities.end()))
	{
		check(destination_ñities, best_permutation, distances, min_sum, start, num_of_destination_cities);
	}
	//std::cout << min_sum << std::endl;
	std::vector<int> path;
	//std::cout << start + 1 << " - starting city" << std::endl;
	/*for (int i : best_permutation)
	{
		std::cout << i + 1 << ' ';
	}
	std::cout << std::endl;*/
	getShortestPath(start, best_permutation[0], distances, next, path);
	for (int i = 0; i < num_of_destination_cities - 1; ++i)
	{
		getShortestPath(best_permutation[i], best_permutation[i + 1], distances, next, path);
	}
	std::vector<int> final_path;
	for (int i = 0; i < path.size() - 1; ++i)
	{
		if (path[i] != path[i + 1])
		{
			final_path.push_back(path[i]);
		}
	}
	final_path.push_back(path[path.size() - 1]);
	std::vector<int> was;
	std::cout << final_path[0] << " - starting city" << std::endl;
	for (int i = 1; i < final_path.size(); ++i)
	{
		if (in(final_path[i] - 1, destination_ñities))
		{
			if (!(in(final_path[i] - 1, was)))
			{
				std::cout << final_path[i] << " - destination city" << std::endl;
				was.push_back(final_path[i]);
			}
			else
			{
				std::cout << final_path[i] << " - transit city" << std::endl;
			}
		}
		else
		{
			std::cout << final_path[i] << " - transit city" << std::endl;
		}
	}
	//system("PAUSE");
	return 0;
}