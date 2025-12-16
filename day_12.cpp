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
#define endl '\n'
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
struct Shape {
    vector<pair<int, int>> cells; /// pozitii relative (linie,coloana) de la top-left
    int minR, maxR, minC, maxC;
    int height, width;
    void normalize() {
        if (cells.empty()) return;
        minR = minC = INT_MAX;
        maxR = maxC = INT_MIN;
        for (auto& [r, c] : cells) {
            minR = min(minR, r);
            maxR = max(maxR, r);
            minC = min(minC, c);
            maxC = max(maxC, c);
        }
        // shift -> origin
        for (auto& [r, c] : cells) {
            r -= minR;
            c -= minC;
        }
        height = maxR - minR + 1;
        width = maxC - minC + 1;
        minR = minC = 0;
        maxR = height - 1;
        maxC = width - 1;
        // sortam pentru forma canonica
        sort(cells.begin(), cells.end());
    }
    Shape rotate90() const {
        // (r, c) -> (c, -r) = (c, height-1-r) dupa normalizare
        Shape s;
        for (auto [r, c] : cells) {
            s.cells.push_back({ c, height - 1 - r });
        }
        s.normalize();
        return s;
    }
    Shape flipH() const {
        Shape s;
        for (auto [r, c] : cells) {
            s.cells.push_back({ r, width - 1 - c });
        }
        s.normalize();
        return s;
    }
    bool operator<(const Shape& o) const {
        return cells < o.cells;
    }
    bool operator==(const Shape& o) const {
        return cells == o.cells;
    }
};
vector<set<Shape>> allVariants; // allVariants[i] = toate rotatiile/flips pentru shape i 
void generateVariants(const Shape& base, set<Shape>& variants) {
    Shape s = base;
    for (int flip = 0; flip < 2; flip++) {
        for (int rot = 0; rot < 4; rot++) {
            variants.insert(s);
            s = s.rotate90();
        }
        s = s.flipH();
    }
}
int gridW, gridH;
vector<vector<int>> grid;
bool canPlace(const Shape& s, int startR, int startC) {
    for (auto [r, c] : s.cells) {
        int nr = startR + r;
        int nc = startC + c;
        if (nr < 0 || nr >= gridH || nc < 0 || nc >= gridW) 
            return false;
        if (grid[nr][nc] != 0) 
            return false;
    }
    return true;
}
void place(const Shape& s, int startR, int startC, int id) {
    for (auto [r, c] : s.cells) {
        grid[startR + r][startC + c] = id;
    }
}
void unplace(const Shape& s, int startR, int startC) {
    for (auto [r, c] : s.cells) {
        grid[startR + r][startC + c] = 0;
    }
}
// gaseste prima celula empty
pair<int, int> findEmpty() {
    for (int r = 0; r < gridH; r++) {
        for (int c = 0; c < gridW; c++) {
            if (grid[r][c] == 0) 
                return { r, c };
        }
    }
    return { -1, -1 };
}
vector<int> remaining; // remaining[i] = cate forme i mai trebuie sa punem
/// Gaseste primul index al unei forme cu remaining > 0
int findNextShape() {
    for (int i = 0; i < (int)remaining.size(); i++) {
        if (remaining[i] > 0) 
            return i;
    }
    return -1;
}
bool solve() {
    int shapeIdx = findNextShape();
    if (shapeIdx == -1) 
        return true; // toate formele au fost puse
    // Incercam toate pozitiile pentru forma aceasta
    for (const Shape& s : allVariants[shapeIdx]) {
        for (int startR = 0; startR <= gridH - s.height; startR++) {
            for (int startC = 0; startC <= gridW - s.width; startC++) {
                if (canPlace(s, startR, startC)) {
                    place(s, startR, startC, shapeIdx + 1);
                    remaining[shapeIdx]--;
                    if (solve()) 
                        return true;
                    remaining[shapeIdx]++;
                    unplace(s, startR, startC);
                }
            }
        }
    }
    return false;
}
void solve1() {
    string line;
    vector<Shape> baseShapes;
    vector<string> regionLines;
    bool parsingShapes = true;
    Shape currentShape;
    int currentRow = 0;
    while (getline(fin, line)) {
        if (parsingShapes) {
            /// Verificam daca este o linie regiune (are 'x' inainte de ':')
            size_t xPos = line.find('x');
            size_t colonPos = line.find(':');
            if (xPos != string::npos && colonPos != string::npos && xPos < colonPos) {
                // linie regiune
                parsingShapes = false;
                regionLines.push_back(line);
                // Salvam forma curenta daca nu e empty
                if (!currentShape.cells.empty()) {
                    currentShape.normalize();
                    baseShapes.push_back(currentShape);
                }
                continue;
            }
            if (line.empty()) {
                // sfarsitul formei curente
                if (!currentShape.cells.empty()) {
                    currentShape.normalize();
                    baseShapes.push_back(currentShape);
                    currentShape = Shape();
                    currentRow = 0;
                }
                continue;
            }
            // Quick check daca este shape header (digit:)
            if (line.size() >= 2 && isdigit(line[0]) && line.find(':') != string::npos) {
                // Incepe o forma noua, salvam cea anterioara (Daca exista)
                if (!currentShape.cells.empty()) {
                    currentShape.normalize();
                    baseShapes.push_back(currentShape);
                }
                currentShape = Shape();
                currentRow = 0;
                continue;
            }
            // Parsam linia formei
            for (int col = 0; col < (int)line.size(); col++) {
                if (line[col] == '#') {
                    currentShape.cells.push_back({ currentRow, col });
                }
            }
            currentRow++;
        }
        else {
            // Parsam regiunile
            if (!line.empty()) 
                regionLines.push_back(line);
        }
    }
    // Salvam ultima forma, daca exista
    if (!currentShape.cells.empty()) {
        currentShape.normalize();
        baseShapes.push_back(currentShape);
    }
    // Generam toate variantele pentru forme
    allVariants.resize(baseShapes.size());
    for (int i = 0; i < (int)baseShapes.size(); i++) {
        generateVariants(baseShapes[i], allVariants[i]);
    }
    int answer = 0;
    // procesam regiunile
    for (const string& regionLine : regionLines) {
        // Parse: WxH: c0 c1 c2 c3 c4 c5
        int W, H;
        sscanf(regionLine.c_str(), "%dx%d:", &W, &H);
        // aflam coloana si parsam numararile
        size_t colonPos = regionLine.find(':');
        string rest = regionLine.substr(colonPos + 1);
        stringstream ss(rest);
        vector<int> counts;
        int cnt;
        while (ss >> cnt) {
            counts.push_back(cnt);
        }
        gridW = W;
        gridH = H;
        grid.assign(H, vector<int>(W, 0));
        remaining = counts;
        int totalPieces = 0;
        int totalCells = 0;
        for (int i = 0; i < (int)counts.size(); i++) {
            totalPieces += counts[i];
            totalCells += counts[i] * (int)baseShapes[i].cells.size();
        }
        // verificam: daca toate cells > arie, imposibil
        if (totalCells > W * H) {
            // imposibil
        }
        else 
            if (totalPieces == 0) 
                answer++;
            else {
                if (solve()) 
                    answer++;
            }
    }
    cout << answer << endl;
}
void solve2() {
    // there is no part2 
    // SEERC is over
    // AOC is over
    // +5 un CS2?
}
int main() {
    FAST;
    solve1();
    //solve2();
    return 0;
}
