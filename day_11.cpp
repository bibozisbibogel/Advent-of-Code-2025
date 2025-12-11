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
/*
vector<pair<int, int>> dir = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},           {0, 1},
    {1, -1},  {1, 0},  {1, 1}
};
ll Euclidean_Distance(const Box& a,const Box& b)
{
    return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
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
*/
//ifstream fin("test.in");
ifstream fin("input.in");
ofstream fout("output.out");
void solve1() {
    string line;
    unordered_map<string, vector<string>> output;
    while (getline(fin, line)) {
        int i = 0;
        int l = line.size();
        bool inainte_de_doua_puncte = true;
        string key = "";
        while (i < l) {
            if (isalpha(line[i]) && inainte_de_doua_puncte==1)
            {
                string word = "";
                while (i < l && isalpha(line[i])) {
                    word += line[i];
                    i++;
                }
                key = word;
            }
            if (line[i] == ':')
            {
                i++;
                inainte_de_doua_puncte = 0;
            }
            if (isspace(line[i]))
                i++;
            if (isalpha(line[i]) && inainte_de_doua_puncte == 0)
            {
                string word = "";
                while (i < l && isalpha(line[i]))
                {
                    word += line[i];
                    i++;
                }
                output[key].push_back(word);
            }
        }
    }
    /*
    for (auto& key : output)
    {
        cout << key.first << ": ";
        for (auto& elem : key.second)
        {
            cout << elem << " ";
        }
        cout << '\n';
    }
    */
    // dfs de la "you" la "out"
    function<ll(const string&)> nr_paths = [&](const string& node) -> ll {
        if (node == "out")
            return 1;
        if (output.find(node) == output.end())
            return 0;
        ll total = 0;
        for (const string& next : output[node])
        {
            total += nr_paths(next);
        }
        return total;
    };
    cout << nr_paths("you");
}
void solve2() {
    string line;
    unordered_map<string, vector<string>> output;
    while (getline(fin, line)) {
        int i = 0;
        int l = line.size();
        bool inainte_de_doua_puncte = true;
        string key = "";
        while (i < l) {
            if (isalpha(line[i]) && inainte_de_doua_puncte == 1)
            {
                string word = "";
                while (i < l && isalpha(line[i])) {
                    word += line[i];
                    i++;
                }
                key = word;
            }
            if (line[i] == ':')
            {
                i++;
                inainte_de_doua_puncte = 0;
            }
            if (isspace(line[i]))
                i++;
            if (isalpha(line[i]) && inainte_de_doua_puncte == 0)
            {
                string word = "";
                while (i < l && isalpha(line[i]))
                {
                    word += line[i];
                    i++;
                }
                output[key].push_back(word);
            }
        }
    }
    // dfs din "svr" in "out", dar sa treaca si prin "dac" si prin "fft"
    // trebuie sa eficientizam dfs-ul -> daca am mai fost intr-o stare cu visited_dac si visited_fft de valoarea respectiva
    // daca am mai fost in starea respectiva inainte -> ii dam valoarea
    // tuple<string,bool,bool> -> nume nod, visited_dac, visited_fft
    /// map<tuple<string,bool,bool>,ll> -> cheia este starea respectiva (nodul cu situatia visited_dac si visited_fft) -> cate paths sunt pana acolo
    map<tuple<string, bool, bool>, ll> cache_paths;
    function<ll(const string&, bool, bool)> nr_paths = [&](const string& node, bool visited_dac, bool visited_fft) -> ll {
        if (node == "dac")
            visited_dac = true;
        if (node == "fft")
            visited_fft = true;
        if (node == "out")
        {
            if (visited_dac == 1 && visited_fft == 1)
                return 1;
            else
                return 0;
        }
        if (output.find(node) == output.end())
            return 0;
        /// iau din cache (daca e)
        auto key = make_tuple(node, visited_dac, visited_fft);
        if (cache_paths.find(key) != cache_paths.end()) // daca e
        {
            return cache_paths[key];
        }
        ll total = 0;
        for (const string& next : output[node])
        {
            total += nr_paths(next, visited_dac, visited_fft);
        }
        cache_paths[key] = total;
        return total;
    };
    cout << nr_paths("svr", false, false);
}
int main() {
    FAST;
    //solve1();
    solve2();
    return 0;
}
