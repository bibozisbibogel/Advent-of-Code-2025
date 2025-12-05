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
/*
vector<pair<int, int>> dir = {
	{-1, -1}, {-1, 0}, {-1, 1},
	{0, -1},           {0, 1},
	{1, -1},  {1, 0},  {1, 1}
};
*/
void solve1() {
	ll answer = 0;
	string line = "";
	vector<pair<ll, ll>>v;
	while (getline(fin, line))
	{
		if (line.empty())
			break;
		ll st, dr;
		char minus;
		stringstream ss(line);
		ss >> st >> minus >> dr;
		v.push_back({ st,dr });
	}
	ll ID;
	while (fin >> ID) {
		bool found = 0;
		for (auto& pereche : v) 
		{
			if (ID >= pereche.first && ID <= pereche.second && found==0)
			{
				found = 1;
				answer++;
			}
		}
	}
	cout << answer;
}
void solve2() {
	ll answer = 0;
	string line = "";
	vector<pair<ll, ll>>v;
	while (getline(fin, line))
	{
		if (line.empty())
			break;
		ll st, dr;
		char minus;
		stringstream ss(line);
		ss >> st >> minus >> dr;
		v.push_back({ st,dr });
	}
	/*
		input:
		3-5
		10-14
		16-20
		12-18
		----------------------------
		le sortam:

		3-5
		10-14
		12-18
		16-20

		le unim pe care putem si ramanem cu intervalele:

		3-5 => (5-3+1) = 3 numere
		10-20 => (20-10+1) = 11 numere

		raspuns: 3+11 = 14 (Adevarat)

		answer=0
		capat_st_curent = 3
		capat_dr_curent = 5

		INCEPE FOR-UL

		st = 10
		dr = 14

		st > capat_dr_curent + 1 ( 10 > 6) ADEVARAT
		deci:

		answer += (5-3+1) => answer = 0 + 3 = 3
		capat_st_curent = st = 10
		capat_dr_curent = dr = 14

		st = 12
		dr = 18

		st > capat_dr_curent+1 ( 12 > 15) FALS
		
		capat_dr_curent = max(capat_dr_curent,dr) = max(14,18) = 18

		st = 16
		dr = 20

		st > capat_dr_curent + 1 ( 16 > 19) FALS

		capat_dr_curent = max(capat_dr_curent,dr) = max (18,20) = 20

		SE TERMINA FOR-UL

		adaugam ultimul interval (cel lipit in cazul asta)

		answer += capat_dr_curent - capat_st_curent +1 => answer = 3 + (20 - 10 + 1 ) = 3 + 11 = 14 (adevarat)

		
	*/
	sort(v.begin(), v.end());
	/// incerc sa unesc intervalele
	ll capat_st_curent = v[0].first;
	ll capat_dr_curent = v[0].second;
	for (int i = 1; i < v.size(); i++)
	{
		ll st = v[i].first;
		ll dr = v[i].second;
		/* 
			
			[3, 5] si[6, 10]... daca aveam st > capat_dr_curent => [3, 10]  
			ne asiguram ca intervalele nu se pot lipi (sunt diferite)

		*/ 
		if (st > capat_dr_curent + 1) // intervale diferite (nu le pot uni)
		{
			answer += (capat_dr_curent - capat_st_curent + 1);
			capat_st_curent = st;
			capat_dr_curent = dr;
		}
		else
			capat_dr_curent = max(capat_dr_curent, dr); /// lipim intervalele
	}
	answer += capat_dr_curent - capat_st_curent + 1;
	ll ID;
	while (fin >> ID) {
		/// nimic;
	}
	cout << answer;
}
int main() {
	FAST;
	//solve1();
	solve2();
	return 0;
}
