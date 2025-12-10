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
ll popcount(ll x) { // cati de 1 are
    ll cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}
struct Button
{
    vector<int>light_switches;
};
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
/*
    Exemplu: [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
    => { 4 contoare => trebuie sa ajungem la {3,5,4,7}
       { 6 butoane

    B0: (3) => afecteaza contorul 3
    B1: (1,3) => afecteaza contoarele 1 si 3
    B2: (2) => afecteaza contorul 2
    B3: (2,3) => afecteaza contoarele 2 si 3
    B4: (0,2) => afecteaza contoarele 0 si 2
    B5: (0,1) => afecteaza contoarele 0 si 1

    => Avem variabilele: x0,x1,x2,x3,x4,x5 (ne dam seama dupa nr de butoane) => de cate ori apasam fiecare buton


    0 => nu are legatura cu contorul respectiv (nu-l poate afecta)
    1 => are legatura (il schimba)
    
    -----------------------------------------------------
    Contor 0: 3 = 0*x0 + 0*x1 + 0*x2 + 0*x3 + 1*x4 + 1*x5
    Contor 1: 5 = 0*x0 + 1*x1 + 0*x2 + 0*x3 + 0*x4 + 1*x5
    Contor 2: 4 = 0*x0 + 0*x1 + 1*x2 + 1*x3 + 1*x4 + 0*x5
    Contor 3: 7 = 1*x0 + 1*x1 + 0*x2 + 1*x3 + 0*x4 + 0*x5
    -----------------------------------------------------
    Contor 0: 3 = x4 + x5
    Contor 1: 5 = x1 + x5
    Contor 2: 4 = x2 + x3 + x4
    Contor 3: 7 = x1 + x3

    => Matricea augmentata = (0 0 0 0 1 1 | 3)
                             (0 1 0 0 0 1 | 5)
                             (0 0 1 1 1 0 | 4)
                             (1 1 0 1 0 0 | 7)
    A = (0 0 0 0 1 1)   si b = (3)
        (0 1 0 0 0 1)          (5)
        (0 0 1 1 1 0)          (4)
        (1 1 0 1 0 0)          (7)

    Avem A*x=b si trebuie sa rezolvam (sa aflam x0,x1,x2,x3,x4,x5).

    Folosim Gauss cu pivotare partiala (adaptat) sa aflam solutiile de fiecare data => rezolvam sistemul

    Etape de rezolvare:
        1. Parsez input-ul => citesc butoanele si voltajele
        2. Construiesc matricea sistemului A*x = b, unde:
           i) A[i][j] = 1 daca butonul j afecteaza contorul i
           ii) b[i] = voltaj[i] (valoarea dorita pt contorul i)
        3. Gauss cu pivotare partiala adaptat pentru cazul acesta, practic o sa facem o eliminare cu fractii exacte pentru a evita erori de precizie
        4. Identificam variabilele libere (coloanele fara pivot)
        5. Cautare pe variabilele libere => pentru fiecare combinatie valida, calculam variabilele pivot si verificam ca sunt >=0 si INTREGI!
        6. Minimizam suma totala de apasari
*/
// structura pentru fractii (pentru Gauss exact) -> adaptam Gauss cu pivotare partiala pentru a rezolva problema
struct Frac {
    ll sus, jos;

    Frac(ll n = 0, ll d = 1) : sus(n), jos(d) {
        normalize();
    }

    ll gcd(ll a, ll b) {
        if (b == 0) {
            return a;
        }
        return gcd(b, a % b);
    }

    void normalize() {
        if (jos < 0) {
            sus = -sus;
            jos = -jos;
        }
        ll g = gcd(abs(sus), abs(jos));
        if (g) {
            sus = sus/g;
            jos = jos/g;
        }
    }

    Frac operator+(const Frac& o) const {
        return Frac(sus * o.jos + o.sus * jos, jos * o.jos);
    }

    Frac operator-(const Frac& o) const {
        return Frac(sus * o.jos - o.sus * jos, jos * o.jos);
    }

    Frac operator*(const Frac& o) const {
        return Frac(sus * o.sus, jos * o.jos);
    }

    Frac operator/(const Frac& o) const {
        return Frac(sus * o.jos, jos * o.sus);
    }

    bool operator==(const Frac& o) const {
        return sus == o.sus && jos == o.jos;
    }

    bool isZero() const {
        return sus == 0;
    }

    bool isInt() const {
        return jos == 1;
    }

    ll toInt() const {
        return sus / jos;
    }
};
void solve2() {
    string line;
    ll final_answer = 0;
    while (getline(fin, line))
    {
        vector<Button> buttons;
        vector<ll> voltaje;
        int l = line.size();
        int i = 0;
        while (i < l)
        {
            if (line[i] == '[') 
            {
                i++;
                while (line[i] != ']') 
                    i++;
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
            if (line[i] == '{') // voltajele 
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
        int m = voltaje.size();    // nr contoare (ecuatii)
        int n = buttons.size();   // nr butoane (variabile)
        // Construim matricea augmentata [A | b] folosind fractii
        vector<vector<Frac>> aug(m, vector<Frac>(n + 1));
        for (int row = 0; row < m; row++) 
        {
            for (int col = 0; col < n; col++) 
            {
                aug[row][col] = Frac(0);
            }
            aug[row][n] = Frac(voltaje[row]);
        }
        for (int button_number = 0; button_number < n; button_number++) 
        {
            for (int counter : buttons[button_number].light_switches) 
            {
                if (counter < m) 
                    aug[counter][button_number] = Frac(1);
            }
        }

        // Eliminare Gaussiana cu pivotare partiala -> Laboratorul 2 Metode Numerice, Anul2
        vector<int> pivot_col(m, -1);
        int pivot_row = 0;

        for (int col = 0; col < n && pivot_row < m; col++) 
        {
            // gasim pivotul maxim in coloana col
            int best = pivot_row;
            for (int row = pivot_row + 1; row < m; row++) {
                if (abs(aug[row][col].sus) > abs(aug[best][col].sus)) 
                    best = row;
            }
            if (aug[best][col].isZero()) 
                continue;
            swap(aug[pivot_row], aug[best]);
            pivot_col[pivot_row] = col;
            // normalizam randul pivot
            Frac pivot_val = aug[pivot_row][col];
            for (int j = col; j <= n; j++) {
                aug[pivot_row][j] = aug[pivot_row][j] / pivot_val;
            }
            // eliminam in toate celelalte randuri
            for (int row = 0; row < m; row++) {
                if (row != pivot_row && !aug[row][col].isZero()) {
                    Frac factor = aug[row][col];
                    for (int j = col; j <= n; j++) {
                        aug[row][j] = aug[row][j] - factor * aug[pivot_row][j];
                    }
                }
            }
            pivot_row++;
        }
        int rank = pivot_row;
        // identificam coloanele libere (fara pivot) -> vrem sa aflam variabilele libere practic
        vector<bool> is_pivot_col(n, false);
        for (int row = 0; row < rank; row++) {
            if (pivot_col[row] >= 0) {
                is_pivot_col[pivot_col[row]] = true;
            }
        }
        vector<int> coloane_libere;
        for (int col = 0; col < n; col++) {
            if (!is_pivot_col[col]) {
                coloane_libere.push_back(col);
            }
        }
        ll max_voltaje = *max_element(voltaje.begin(), voltaje.end());
        ll min_presses = LLONG_MAX;
        int n_libere = coloane_libere.size();
        vector<ll> variabile_libere(n_libere, 0);
        vector<ll> limita_superiora_variabile_libere(n_libere, max_voltaje);
        // functie pentru a calcula solutia data de valorile variabilelor libere
        auto calculeaza_solutia = [&](const vector<ll>& fv) -> pair<bool, ll> {
            vector<Frac> x(n, Frac(0));
            // setam variabilele libere
            for (int i = 0; i < n_libere; i++) {
                x[coloane_libere[i]] = Frac(fv[i]);
            }
            // calculam variabilele pivot mergand in spate 
            for (int row = rank - 1; row >= 0; row--) {
                int pc = pivot_col[row];
                if (pc < 0) 
                    continue;
                Frac sum = aug[row][n];
                for (int col = 0; col < n; col++) 
                {
                    if (col != pc) 
                        sum = sum - aug[row][col] * x[col];
                }
                x[pc] = sum;
            }
            // verificam ca toate sunt >=0 si INTREGI!!!!!!!!
            ll total = 0;
            for (int col = 0; col < n; col++) {
                if (!x[col].isInt())
                    return make_pair(false, 0LL);
                ll val = x[col].toInt();
                if (val < 0) 
                    return make_pair(false, 0LL);
                total += val;
            }
            return make_pair(true, total);
        };
        // cautare recursiva pe variabilele libere
        function<void(int, ll)> search = [&](int idx, ll current_sum) {
            if (current_sum >= min_presses) 
                return;
            if (idx == n_libere) {
                pair<bool, ll> result = calculeaza_solutia(variabile_libere);
                if (result.first && result.second < min_presses) {
                    min_presses = result.second;
                }
                return;
            }
            for (ll val = 0; val <= limita_superiora_variabile_libere[idx]; val++) {
                variabile_libere[idx] = val;
                search(idx + 1, current_sum + val);
            }
        };
        for (int i = 0; i < n_libere; i++) {
            limita_superiora_variabile_libere[i] = min(max_voltaje, (ll)300);
        }
        search(0, 0);
        if (min_presses == LLONG_MAX) 
            min_presses = 0;
        final_answer += min_presses;
    }
    cout << final_answer;
}
int main() {
    FAST;
    //solve1();
    solve2();
    return 0;
}
