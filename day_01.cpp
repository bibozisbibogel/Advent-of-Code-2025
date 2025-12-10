#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <climits>
#include <sstream>
#include <string.h>
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define ll long long
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");
void solve1() {
	/// 0 -> 99
	int start = 50; /// o sa fie mereu intre 0 si 99
	ll answer = 0;
	string line;
	while (getline(fin, line)) {
		if (line.size() == 0)
			continue;
		char direction = line[0];
		ll number = stoll(line.substr(1));
		if (direction == 'L')
		{
			start = (start - number % 100 + 100) % 100;
		}
		else
			if (direction == 'R')
				start = (start + number) % 100;
		if (start == 0)
			answer++;
	}
	cout << answer;
}
void solve2() {
	int start = 50;
	ll answer = 0;
	string line;
	while (getline(fin, line)) {
		if (line.size() == 0)
			continue;
		char direction = line[0];
		ll number = stoll(line.substr(1));
		answer += number / 100; /// ture intregi
		int ramas = number % 100;
		for (int i = 0; i < ramas; i++)
		{
			if (direction == 'R')
			{
				start = (start + 1) % 100;
			}
			else
			{
				start = (start - 1 + 100) % 100;
			}
			if (start == 0)
				answer++;
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
