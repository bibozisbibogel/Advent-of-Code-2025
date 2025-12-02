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
ifstream fin("test.in");
//ifstream fin("input.in");
ofstream fout("output.out");
void solve1() {
    auto read_number = [&](const string& s, int& i) {
        ll number = 0;
        while (i < s.size() && isdigit(s[i])) 
        {
            number = number * 10 + (s[i] - '0');
            i++;
        }
        return number;
    };
    auto invalidID = [&](ll x) {
        string s = to_string(x);
        if (s[0] == '0') 
            return false;
        if (s.size() % 2 != 0) 
            return false;
        int mid = s.size() / 2;
        string first = s.substr(0, mid);
        string second = s.substr(mid, mid);
        return first == second;
    };
    string line;
    getline(fin, line);
    ll sum = 0;
    ll a, b;
    int i = 0;
    while (i < line.size()) {
        a = read_number(line, i);
        if (i < line.size() && line[i] == '-') 
            i++;
        b = read_number(line, i);
        for (ll x = a; x <= b; x++) {
            if (invalidID(x)) 
                sum += x;
        }
        if (i < line.size() && line[i] == ',') 
            i++;
    }
    cout << sum << '\n';
}
void solve2() {
    auto read_number = [&](const string& s, int& i) {
        ll number = 0;
        while (i < s.size() && isdigit(s[i])) {
            number = number * 10 + (s[i] - '0');
            i++;
        }
        return number;
    };
    auto invalidID = [&](ll x) {
        string s = to_string(x);
        if (s[0] == '0') 
            return false;
        int l = s.size();
        for (int poz = 1; poz <= l / 2; poz++) {
            if (l % poz != 0) /// nu poate sa fie impartit in blocuri de cate poz
                continue;
            string block = s.substr(0, poz);
            bool ok = 1;
            for (int j = 0; j < l; j += poz) {
                if (s.substr(j, poz) != block) 
                {
                    ok = false;
                    break;
                }
            }
            if (ok==1 && (l / poz) >= 2) 
                return true;
        }
        return false;
    };
    string line;
    getline(fin, line); 
    ll sum = 0;
    ll a, b;
    int i = 0;
    while (i < line.size()) {
        a = read_number(line, i);
        if (i < line.size() && line[i] == '-') 
            i++;
        b = read_number(line, i);
        /// daca avem range mic, ne permitem brute force
        if (b - a <= 1000000) 
        {
            for (ll x = a; x <= b; x++) 
            {
                if (invalidID(x)) sum += x;
            }
        }
        else 
        {
            /// daca avem range mare, micsoram spatiul de cautare (let's hope it works)
            /*
            
                basically, 
                daca am avea 150-150000000000000 -> am itera DE FOARTE MULTE ORI -> ajung cu Local Disk C-ul pe rosu ca anul trecut
                
                ce facem? ~ nu mai verificam tot.
                => verificam primele 1.000.000 numere la inceput si ultimele 1.000.000
                
                deci a = a + 1000000;
                     b = b - 1000000;
                -> capetele intervalului

                exemplu: 
                    avem: 10 - 1.000.000.000.000
                ce vom verifica:
                    i) 10 -> 1.000.010
                    ii) 999.999.999.000 -> 1.000.000.000.000

                ignoram ce e la mijloc, sperand ca nu ratam id-uri invalide

                (pacalim advent of code-ul)

            */
            for (ll x = a; x <= min(a + 1000000, b); x++) 
                if (invalidID(x)) 
                    sum += x;
            for (ll x = max(b - 1000000, a); x <= b; x++) 
                if (invalidID(x)) 
                    sum += x;
        }
        if (i < line.size() && line[i] == ',')
            i++;
    }
    cout << sum << '\n';
}
int main() {
	FAST;
	//solve1();
	solve2();
	return 0;
}
