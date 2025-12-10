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
    string line;
    vector<string> linii;
    string last_line;
    while (getline(fin, line)) {
        bool este_operatie = 1;
        for (char c : line) {
            if (c != ' ' && c != '+' && c != '*') 
            {
                este_operatie = 0;
                break;
            }
        }
        if (este_operatie==1) {
            last_line = line;
            break;
        }
        linii.push_back(line);
    }
    int nr_coloane = 0;
    {
        string line = linii[0];
        int i = 0;
        while (i < line.size()) 
        {
            if (isdigit(line[i])) 
            {
                while (i < line.size() && isdigit(line[i])) {
                    i++;
                }
                nr_coloane++;
            }
            else 
                i++;
        }
    }
    vector<vector<ll>> matrice;
    matrice.resize(nr_coloane);
    for (auto& l : linii) {
        int i = 0, col = 0;
        while (i < l.size()) 
        {
            if (isdigit(l[i])) 
            {
                ll number = 0;
                while (i < l.size() && isdigit(l[i])) 
                {
                    number = number * 10 + l[i] - '0';
                    i++;
                }
                matrice[col].push_back(number);
                col++;
            }
            else 
                i++;
        }
    }
    vector<char> operatie;
    operatie.resize(nr_coloane);
    int col = 0;
    for (char& c : last_line) {
        if (c == '+' || c == '*') {
            operatie[col] = c;
            col++;
        }
    }
    ll sum = 0;
    for (int c = 0; c < nr_coloane; c++) {
        if (operatie[c] == '+') {
            ll suma_numere = 0;
            for (auto& elem : matrice[c]) 
                suma_numere += elem;
            sum += suma_numere;
        }
        else 
        {
            ll produs_numere = 1;
            for (auto& elem : matrice[c]) 
                produs_numere *= elem;
            sum += produs_numere;
        }
    }
    cout << sum;
}
void solve2() {
    string line;
    vector<string> linii;
    string last_line;
    while (getline(fin, line))
    {
        bool este_operatie = 1;
        for (char& c : line)
        {
            if (c != ' ' && c != '+' && c != '*')
            {
                este_operatie = 0;
                break;
            }
        }
        if (este_operatie == 1)
        {
            last_line = line;
            break;
        }
        linii.push_back(line);
    }
    int nr_linii = (int)linii.size();
    int nr_coloane = (int)linii[0].size();
    ll sum = 0;
    vector<ll> current;
    char current_op = 0;
    for (int j = nr_coloane - 1; j >= 0; j--)
    {
        bool numai_spatii = 1;
        string numar = "";
        for (int i = 0; i < nr_linii; i++)
        {
            char c = linii[i][j];
            if (c != ' ')
                numai_spatii = 0;
            if (isdigit(c))
                numar.push_back(c);
        }
        char op_c = last_line[j];
        if (numai_spatii && op_c == ' ')
        {
            if (!current.empty())
            {
                if (current_op == '+')
                {
                    ll suma_numere = 0;
                    for (auto& elem : current) 
                        suma_numere += elem;
                    sum += suma_numere;
                }
                else 
                    if (current_op == '*')
                    {
                        ll produs_numere = 1;
                        for (auto& elem : current)
                            produs_numere *= elem;
                        sum += produs_numere;
                    }
                 current.clear();
                 current_op = 0;
            }
            continue;
        }
        if (!numar.empty())
        {
            ll x = stoll(numar);
            current.push_back(x);
        }
        if (op_c == '+' || op_c == '*')
        {
           current_op = op_c;
        }
    }
    if (!current.empty())
    {
        if (current_op == '+')
        {
            ll suma_numere = 0;
            for (auto& elem :  current) 
                suma_numere += elem;
            sum += suma_numere;
        }
        else 
            if (current_op == '*')
            {
                ll produs_numere = 1;
                for (auto& elem : current) 
                    produs_numere *= elem;
                sum += produs_numere;
            }
    }
    cout << sum;
}
int main() {
	FAST;
	//solve1();
	solve2();
	return 0;
}
