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
struct Box
{
	ll x;
	ll y;
	ll z;
	bool operator<(const Box& other) const {
		if (this->x != other.x) 
			return this->x < other.x;
		if (this->y != other.y) 
			return this->y < other.y;
		return this->z < other.z;
	}
};
/*
ll Euclidean_Distance(const Box& a,const Box& b)
{
	return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
*/
ll dist2(const Box& a, const Box& b)
{
	ll dx = a.x - b.x;
	ll dy = a.y - b.y;
	ll dz = a.z - b.z;
	return dx * dx + dy * dy + dz * dz;
}
vector<int>parinte_UF, marime_UF;
int find_set(int x) {
	if (parinte_UF[x] == x)
		return x;
	return parinte_UF[x] = find_set(parinte_UF[x]);
}
void union_set(int a, int b)
{
	a = find_set(a);
	b = find_set(b);
	if (a != b)
	{
		if (marime_UF[a] < marime_UF[b])
			swap(a, b);
		parinte_UF[b] = a;
		marime_UF[a] += marime_UF[b];
	}
}
void solve1() {
	string line;
	vector<Box> boxes;
	ll x, y, z;
	char c;
	while (fin >> x >> c >> y >> c >> z)
	{
		boxes.push_back({ x,y,z });
	}
	/*
	for (auto& box : boxes)
	{
		cout << box.x << " " << box.y << " " << box.z << "\n";
	}
	*/
	int n = boxes.size();
	vector<tuple<ll, int, int>>edges; /// tuple de: dist2 si nod1 si nod2
	edges.reserve(1LL*n * (n-1)/2);
	for (int i = 0; i < n-1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			edges.push_back(tuple<ll, int, int>(dist2(boxes[i], boxes[j]), i, j));
		}
	}
	sort(edges.begin(), edges.end(), [&](const tuple<ll,int,int>& a,const tuple<ll,int,int>& b) {
		if (get<0>(a) != get<0>(b))
			return get<0>(a) < get<0>(b);
		if (get<1>(a) != get<1>(b))
			return get<1>(a) < get<1>(b);
		return get<2>(a) < get<2>(b);
		});
	parinte_UF.resize(n);
	marime_UF.resize(n, 1);
	for (int i = 0; i < n; i++)
	{
		parinte_UF[i] = i;
	}
	//int de_cate_ori_exemplu = 10;
	int de_cate_ori = 1000;
	for (int i = 0; i < de_cate_ori; i++)
	{
		tuple<ll, int, int> pereche = edges[i];
		if (find_set(get<1>(pereche)) != find_set(get<2>(pereche)))
			union_set(get<1>(pereche), get<2>(pereche));
	}
	unordered_map<int, int> circuite; /// index -> cate elemente are multimea in care se afla
	for (int i = 0; i < n; i++)
	{
		circuite[find_set(i)]++;
	}
	vector<int> marimi_circuite;
	for (auto& elem : circuite)
	{
		marimi_circuite.push_back(elem.second);
	}
	sort(marimi_circuite.begin(), marimi_circuite.end(), [&](const int& a, const int& b) {
		return a > b;
		});
	long long ans = 1;
	ans = ans * marimi_circuite[0] * marimi_circuite[1] * marimi_circuite[2];
	cout << ans;
}
void solve2() {
	string line;
	vector<Box> boxes;
	long long x, y, z;
	char c;
	while (fin >> x >> c >> y >> c >> z)
	{
		boxes.push_back({ x,y,z });
	}
	/*
	for (auto& box : boxes)
	{
		cout << box.x << " " << box.y << " " << box.z << "\n";
	}
	*/
	int n = boxes.size();
	vector<tuple<ll, int, int>>edges; /// tuple de: dist2 si nod1 si nod2
	edges.reserve(1LL * n * (n - 1) / 2);
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			edges.push_back(tuple<ll, int, int>(dist2(boxes[i], boxes[j]), i, j));
		}
	}
	sort(edges.begin(), edges.end(), [&](const tuple<ll, int, int>& a, const tuple<ll, int, int>& b) {
		if (get<0>(a) != get<0>(b))
			return get<0>(a) < get<0>(b);
		if (get<1>(a) != get<1>(b))
			return get<1>(a) < get<1>(b);
		return get<2>(a) < get<2>(b);
		});
	parinte_UF.resize(n);
	marime_UF.resize(n, 1);
	for (int i = 0; i < n; i++)
	{
		parinte_UF[i] = i;
	}

	int last_i = -1, last_j = -1;
	for (int i = 0; i < edges.size(); i++)
	{
		int a = get<1>(edges[i]);
		int b = get<2>(edges[i]);
		if (find_set(a) != find_set(b))
		{
			union_set(a, b);
			last_i = a;
			last_j = b;
			if (marime_UF[find_set(a)] == n)
				break;
		}
	}
	cout << boxes[last_i].x* boxes[last_j].x;
}
int main() {
	FAST;
	//solve1();
	solve2();
	return 0;
}
