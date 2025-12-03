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
map<int, bool> pozitie_folosita; /// daca pozitia a fost folosita sau nu
void solve1() {
	ll sum = 0;
	string line;
	while (getline(fin, line)) {
		ll Max = 0;
		string number = "";
		for (int i = 0; i < line.size()-1; i++)
		{
			number = line[i];
			for (int j = i + 1; j < line.size(); j++)
			{
				number += line[j];
				//cout << number << " ";
				Max = max(Max, stoll(number));
				number.erase(1,1);
			}
		}
		//cout << Max << '\n';
		sum += Max;
	}
	//cout << '\n';
	cout << sum;
}
void solve2() {
	ll sum = 0;
	string line;
	while (getline(fin, line)) {
		int n = line.size();
		int start = 0;
		int de_gasit = 12;
		string number = "";
		pozitie_folosita.clear();
		while (de_gasit > 0)
		{
			char Max_Cif = -1;
			int poz = -1;
			int capat_dr = n - (de_gasit - 1);
			for (int i = start; i < capat_dr; i++) 
			{
				if (pozitie_folosita[i] == 0 && line[i] > Max_Cif)
				{
					Max_Cif = line[i];
					poz = i;
				}
			}
			if (poz != -1)
			{
				number += line[poz];
				pozitie_folosita[poz] = true;
				start = poz + 1;
			}
			de_gasit--;
		}
		sum += stoll(number);
	}
	cout << sum;
}
int main() {
	FAST;
	//solve1();
	solve2();
	return 0;
}
