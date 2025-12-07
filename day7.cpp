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
#include <functional>
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define ll long long
using namespace std;
//ifstream fin("test.in");
ifstream fin("input.in");
ofstream fout("output.out");
/*
vector<pair<int, int>> dir = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1},           {0, 1},
	{1, -1},  {1, 0},  {1, 1}
};
*/
void solve1() {
	vector<string>matrice;
	string line;
	while (getline(fin, line))
	{
		if (line.size())
			matrice.push_back(line);
	}
	int nr_linii = matrice.size();
	int nr_coloane = matrice[0].size();
	int linie_S = -1, coloana_S = -1;
	for (int i = 0; i < nr_linii; i++)
	{
		for (int j = 0; j < nr_coloane; j++)
		{
			if (matrice[i][j] == 'S')
			{
				linie_S = i;
				coloana_S = j;
			}
		}
	}
	vector<vector<bool>>visited(nr_linii, vector<bool>(nr_coloane, false)); // a inceput deja s-o ia in jos de-acolo
	queue<pair<int, int>>q;
	if (linie_S + 1 < nr_linii)
		q.push({ linie_S + 1,coloana_S });
	ll splits = 0;
	while (!q.empty())
	{
		pair<int, int> pereche = q.front();
		/// pereche.first -> randul
		/// pereche.second -> coloana
		q.pop();
		while (1>0)
		{
			if (pereche.first < 0 || pereche.first >= nr_linii || pereche.second < 0 || pereche.second >= nr_coloane)
				break;
			if (visited[pereche.first][pereche.second] == 1)
				break;
			visited[pereche.first][pereche.second] = 1;
			if (matrice[pereche.first][pereche.second] == '.')
			{
				pereche.first++;
				continue;
			}
			if (matrice[pereche.first][pereche.second] == '^')
			{
				splits++;
				if (pereche.second - 1 >= 0)
					q.push({ pereche.first,pereche.second - 1 });
				if (pereche.second + 1 < nr_coloane)
					q.push({ pereche.first,pereche.second + 1 });
				break;
			}
			pereche.first++;
		}
	}
	cout << splits;
}
void solve2() {
	vector<string>matrice;
	string line;
	while (getline(fin, line))
	{
		if (line.size())
			matrice.push_back(line);
	}
	int nr_linii = matrice.size();
	int nr_coloane = matrice[0].size();
	int linie_S = -1, coloana_S = -1;
	for (int i = 0; i < nr_linii; i++)
	{
		for (int j = 0; j < nr_coloane; j++)
		{
			if (matrice[i][j] == 'S')
			{
				linie_S = i;
				coloana_S = j;
			}
		}
	}
	/*
		Fie matrice[rand][coloana] caracterul curent:
			1. nu se afla in matrice => 1 timeline
			2. matrice[rand][coloana] == '.' => mergem in jos => apel recursiv de (rand+1,coloana)
			3. matrice[rand][coloana] == 'S' => exact ca la 2
			4. matrice[rand][coloana] == '^'=> se da split, o luam la stanga si dreapta => (rand,coloana-1) si (rand,coloana+1)

		Fie dp functia recursiva:
			1. dp(rand,coloana) = 1
			2. dp(rand,coloana) = dp(rand+1,coloana)
			3. dp(rand,coloana) = dp(rand+1,coloana)
			4. dp(rand,coloana) = dp(rand,coloana-1) + dp(rand,coloana+1)

		observatie: trebuie sa am grija sa nu intru de mai multe ori intr-un timeline (atunci cand am ^.^) -> la mijloc o sa fie acelasi timeline, nu trebuie sa-l numar de 2 ori
	*/
	vector<vector<ll>>timelines(nr_linii, vector<ll>(nr_coloane, -1));
	function<ll(int,int)> dp = [&](int linie, int coloana) -> ll {
		if (linie < 0 || linie >= nr_linii || coloana < 0 || coloana >= nr_coloane)
			return 1;
		long long& timeline_number = timelines[linie][coloana];
		if (timeline_number != -1)
			return timeline_number;
		if (matrice[linie][coloana] == '.')
		{
			timeline_number = dp(linie + 1, coloana);
			return timeline_number;
		}
		if (matrice[linie][coloana] == 'S')
		{
			timeline_number = dp(linie + 1, coloana);
			return timeline_number;
		}
		if (matrice[linie][coloana] == '^') {
			ll st = dp(linie, coloana - 1);
			ll dr = dp(linie, coloana + 1);
			timeline_number = st + dr;
			return timeline_number;
		}
	};
	ll answer = dp(linie_S + 1, coloana_S);
	cout << answer;
}
int main() {
	FAST;
	//solve1();
	solve2();
	return 0;
}
