#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <deque>
#include <cmath>
#include <climits>
#include <string>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <string.h>
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define ll long long
using namespace std;
//ifstream fin("test.in");
ifstream fin("input.in");
ofstream fout("output.out");
vector<pair<int, int>> dir = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1},           {0, 1},
	{1, -1},  {1, 0},  {1, 1}
};
void solve1() {
	vector<vector<char>>matrix;
	string line;
	ll answer = 0;
	auto print_matrix = [&](vector<vector<char>>&matrice) {
		for (auto& row : matrice)
		{
			for (auto& caracter : row)
			{
				cout << caracter;
			}
			cout << '\n';
		}
	};
	auto valid = [&](int linie, int coloana, vector<vector<char>>&matrice) {
		return linie >= 0 && linie < matrice.size() && coloana >= 0 && coloana < matrice[0].size();
	};
	while (getline(fin, line)) {
		vector<char> row;
		for (char caracter : line) {
			row.push_back(caracter);
		}
		if (!row.empty())
			matrix.push_back(row);
	}
	//print_matrix(matrix);
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			if (matrix[i][j] == '@')
			{
				int nr = 0;
				/// trebuie sa vedem daca avem @ in jurul elementului
				for (auto& d : dir) 
				{
					int new_i = i + d.first;
					int new_j = j + d.second;
					if (valid(new_i, new_j, matrix)  &&	matrix[new_i][new_j] == '@') 
					{
						nr++;
					}
				}
				if (nr < 4)
					answer++;
			}
		}
	}
	cout << answer;
}
void solve2() {
	vector<string>matrix;
	string line;
	ll answer = 0;
	auto valid = [&](int i, int j) {
		return i >= 0 && i < (int)matrix.size() && j >= 0 && j < (int)matrix[0].size();
	};
	while (getline(fin, line)) {
		if (!line.empty())
			matrix.push_back(line);
	}
	bool changed = 1; /// sa vedem daca s-a schimbat sau nu sa stim daca iesim
	while (changed)
	{
		changed = 0;
		queue<pair<int, int>> q;
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[0].size(); j++)
			{
				if (matrix[i][j] == '@')
				{
					int nr = 0;
					for (auto& d : dir)
					{
						int new_i = i + d.first;
						int new_j = j + d.second;
						if (valid(new_i, new_j) && matrix[new_i][new_j] == '@')
							nr++;
					}
					if (nr < 4)
						q.push({ i,j }); /// salvez coordonatele fiecarui caracter '@' in coada ca dupa sa le transform in '.' 
				}
			}
		}
		while (!q.empty()) {
			pair<int, int> coordonate = q.front();
			q.pop();
			if (matrix[coordonate.first][coordonate.second] == '@')
			{
				matrix[coordonate.first][coordonate.second] = '.';
				answer++;
				changed = 1;
			}
		}
	}
	cout << answer;
}
int main() {
	FAST;
	//solve1();
	solve2();
	return 0;
}
