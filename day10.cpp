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
struct Button
{
    vector<int>light_switches;
};
//ifstream fin("test.in");
ifstream fin("input.in");
ofstream fout("output.out");
ll popcount(ll x) { // cati de 1 are
    ll cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}
void solve1() {
    string line;
    ll final_answer = 0;
    while (getline(fin, line))
    {
        vector<bool> light_desired_states;
        vector<Button> buttons;
        vector<ll> voltaje;
        int l = line.size();
        int i = 0;
        while (i < l)
        {
            if (line[i] == '[') /// aici aflam light states
            {
                ll nr_light = 0;
                i++;
                while (line[i] != ']')
                {
                    if (line[i] == '.')
                    {
                        light_desired_states.emplace_back(0);
                        nr_light++;
                    }
                    else
                        if (line[i] == '#')
                        {
                            light_desired_states.emplace_back(1);
                            nr_light++;
                        }
                    i++;
                }
                i++;
            }
            if (isspace(line[i]))
                i++;
            if (line[i] == '(')
            {
                Button button;
                i++;
                while (line[i] != ')')
                {
                    if (isdigit(line[i]))
                    {
                        ll number = 0;
                        while (i < l && isdigit(line[i]))
                        {
                            number = number * 10 + line[i] - '0';
                            i++;
                        }
                        button.light_switches.emplace_back(number);
                    }
                    if (line[i] == ',')  
                        i++;
                }
                buttons.emplace_back(button);
                i++;
            }
            if (line[i] == '{') /// voltajele
            {
                i++;
                while (line[i] != '}')
                {
                    if (isdigit(line[i]))
                    {
                        ll number = 0;
                        while (i < l && isdigit(line[i]))
                        {
                            number = number * 10 + line[i] - '0';
                            i++;
                        }
                        voltaje.emplace_back(number);
                    }
                    if (line[i] == ',')
                        i++;
                }
                i++;
            }
        }
        /*
        for (int k=0;k<light_desired_states.size();k++)
            cout << light_desired_states[k] << " ";
        cout << '\n';
        */
        ll answer = INT_MAX;
        ll nr_buttons = buttons.size();
        ll nr_lights = light_desired_states.size();
        /*
            exemplu: avem 6 butoane -> avem 2^6 = 64 variante posibile 
            mask = 0 -> 000000 -> nu apas niciun buton
            mask = 1 -> 000001 -> apas doar butonul 0
            mask = 5 -> 000101 -> apas butoanele 0 si 2
            mask = 63 -> 111111 -> apas toate cele 6 butoane
        */
        for (ll mask = 0; mask < (1 << nr_buttons); mask++) /// luam toate posibilitatile -> 2^(nr_buttons)
        {
            ll presses = popcount(mask); /// vad cati de 1 sunt ca sa-mi dau seama cate butoane am apasat
            vector<bool>light_current_states(nr_lights, 0);
            for (int button_number = 0; button_number < nr_buttons; button_number++)
            {
                if (mask & (1 << button_number)) /// daca butonul este apasat
                {
                    for (auto& elem : buttons[button_number].light_switches)
                    {
                        light_current_states[elem] = !light_current_states[elem];
                    }
                }
            }
            if (light_current_states == light_desired_states)
                answer = min(answer, presses);
        }
        final_answer += answer;
    }
    cout << final_answer;
}
void solve2() {
  
}
int main() {
    FAST;
    solve1();
    //solve2();
    return 0;
}
