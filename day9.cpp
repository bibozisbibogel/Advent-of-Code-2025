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
    ll x, y;
    char c;
    vector<pair<ll, ll>> coordonate;
    while (fin >> x >> c >> y)
    {
        coordonate.push_back(make_pair(x, y));
    }
    ll ans = 0;
    for (int i = 0; i < coordonate.size(); i++)
    {
        for (int j = i + 1; j < coordonate.size(); j++)
        {
            ll dx = llabs(coordonate[i].first - coordonate[j].first);
            ll dy = llabs(coordonate[i].second - coordonate[j].second);
            ll arie = (dx + 1) * (dy + 1);
            ans = max(arie, ans);
        }
    }
    cout << ans;
}
void solve2() {
    ll x, y;
    char c;
    vector<pair<ll, ll>> coordonate;
    while (fin >> x >> c >> y)
    {
        coordonate.push_back(make_pair(x, y));
    }

    int n = coordonate.size();
    /// salvam toate segmentele orizontale si verticale ale poligonului
    vector<tuple<ll, ll, ll>> h_segments; // (y, x_min, x_max)
    vector<tuple<ll, ll, ll>> v_segments; // (x, y_min, y_max)

    for (int i = 0; i < n; i++)
    {
        ll x1 = coordonate[i].first;
        ll y1 = coordonate[i].second;
        ll x2 = coordonate[(i + 1) % n].first;
        ll y2 = coordonate[(i + 1) % n].second;
        if (y1 == y2) {
            h_segments.push_back({ y1, min(x1, x2), max(x1, x2) });
        }
        else {
            v_segments.push_back({ x1, min(y1, y2), max(y1, y2) });
        }
    }
    // Raycasting folosind poligonul original (nu cel extins)
    auto ray_casting = [&](ll X, ll Y) {
        bool inside = false;
        for (int i = 0, j = n - 1; i < n; j = i++)
        {
            ll x_i = coordonate[i].first;
            ll y_i = coordonate[i].second;
            ll x_j = coordonate[j].first;
            ll y_j = coordonate[j].second;
            if (y_i == y_j) 
                continue; // dam skip la margini orizontale
            bool intersect = ((y_i > Y) != (y_j > Y)) &&    (X < (x_j - x_i) * (double)(Y - y_i) / (y_j - y_i) + x_i);
            if (intersect)
                inside = !inside;
        }
        return inside;
        };
    // verificam daca punctul este pe marginea poligonului
    auto pe_margine = [&](ll X, ll Y) {
        for (int i = 0; i < h_segments.size(); i++) {
            ll hy = get<0>(h_segments[i]);
            ll hx1 = get<1>(h_segments[i]);
            ll hx2 = get<2>(h_segments[i]);
            if (Y == hy && X >= hx1 && X <= hx2) 
                return true;
        }
        for (int i = 0; i < v_segments.size(); i++) {
            ll vx = get<0>(v_segments[i]);
            ll vy1 = get<1>(v_segments[i]);
            ll vy2 = get<2>(v_segments[i]);
            if (X == vx && Y >= vy1 && Y <= vy2) 
                return true;
        }
        return false;
        };
    auto inauntru_sau_margine = [&](ll X, ll Y) {
        return pe_margine(X, Y) || ray_casting(X, Y);
        };
    // Verificam daca segmentele orizontale [x1,x2] la inaltimea y sunt cu totul inauntru poligonului
    auto h_segment_inside = [&](ll y, ll x1, ll x2) {
        // verificam endpoints
        if (!inauntru_sau_margine(x1, y)) 
            return false;
        if (!inauntru_sau_margine(x2, y)) 
            return false;
        /// colectam toate coordonatele x unde marginile verticale trec nivelul y
        vector<ll> crossings;
        for (int i = 0; i < v_segments.size(); i++) {
            ll vx = get<0>(v_segments[i]);
            ll vy1 = get<1>(v_segments[i]);
            ll vy2 = get<2>(v_segments[i]);
            if (vx > x1 && vx < x2 && y >= vy1 && y <= vy2) {
                crossings.push_back(vx);
            }
        }
        sort(crossings.begin(), crossings.end());
        /// verificam midpoints dintre treceri
        ll prev = x1;
        for (ll cx : crossings) {
            ll mid = (prev + cx) / 2;
            if (!inauntru_sau_margine(mid, y)) 
                return false;
            prev = cx;
        }
        ll mid = (prev + x2) / 2;
        if (!inauntru_sau_margine(mid, y)) 
            return false;
        return true;
        };
    /// Verificam daca segmentul vertical [y1,y2] la pozitia x este cu totul inauntru poligonului
    auto v_segment_inside = [&](ll x, ll y1, ll y2) {
        if (!inauntru_sau_margine(x, y1)) 
            return false;
        if (!inauntru_sau_margine(x, y2)) 
            return false;
        vector<ll> crossings;
        for (int i = 0; i < h_segments.size(); i++) {
            ll hy = get<0>(h_segments[i]);
            ll hx1 = get<1>(h_segments[i]);
            ll hx2 = get<2>(h_segments[i]);
            if (hy > y1 && hy < y2 && x >= hx1 && x <= hx2) {
                crossings.push_back(hy);
            }
        }
        sort(crossings.begin(), crossings.end());
        ll prev = y1;
        for (ll cy : crossings) {
            ll mid = (prev + cy) / 2;
            if (!inauntru_sau_margine(x, mid)) 
                return false;
            prev = cy;
        }
        ll mid = (prev + y2) / 2;
        if (!inauntru_sau_margine(x, mid)) 
            return false;
        return true;
        };
    ll answer = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            ll x1 = coordonate[i].first, y1 = coordonate[i].second;
            ll x2 = coordonate[j].first, y2 = coordonate[j].second;
            ll x_Min = min(x1, x2);
            ll y_Min = min(y1, y2);
            ll x_Max = max(x1, x2);
            ll y_Max = max(y1, y2);
            /// verificam toate cele 4 margini sa fie inauntru poligonului
            /// daca una din conditii nu e indeplinita, nu e rectangle valid
            if (!h_segment_inside(y_Min, x_Min, x_Max))
                continue;
            if (!h_segment_inside(y_Max, x_Min, x_Max)) 
                continue;
            if (!v_segment_inside(x_Min, y_Min, y_Max)) 
                continue;
            if (!v_segment_inside(x_Max, y_Min, y_Max)) 
                continue;
            ll arie = (x_Max - x_Min + 1) * (y_Max - y_Min + 1);
            answer = max(answer, arie);
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
