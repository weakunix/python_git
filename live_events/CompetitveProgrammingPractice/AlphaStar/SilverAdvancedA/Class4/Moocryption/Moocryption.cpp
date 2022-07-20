#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int MostMoos(const vector<string>& Puzzle, const char m, const char o, const int N, const int M) {
    int Total = 0;
    if (m == 'Q' and o == 'M')
        cout << "";
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (Puzzle[y][x] == m) {
                if (x >= 2 and (Puzzle[y][x - 1] == o and Puzzle[y][x - 2] == o)) Total++;
                if (x <= N - 3 and (Puzzle[y][x + 1] == o and Puzzle[y][x + 2] == o)) Total++;
                if (y >= 2 and (Puzzle[y - 1][x] == o and Puzzle[y - 2][x] == o)) Total++;
                if (y <= N - 3 and (Puzzle[y + 1][x] == o and Puzzle[y + 2][x] == o)) Total++;
                if ((x >= 2 and y >= 2) and (Puzzle[y - 1][x - 1] == o and Puzzle[y - 2][x - 2] == o)) Total++;
                if ((x >= 2 and y <= N - 3) and (Puzzle[y + 1][x - 1] == o and Puzzle[y + 2][x - 2] == o)) Total++;
                if ((x <= N - 3 and y >= 2) and (Puzzle[y - 1][x + 1] == o and Puzzle[y - 2][x + 2] == o)) Total++;
                if ((x <= N - 3 and y <= N - 3) and (Puzzle[y + 1][x + 1] == o and Puzzle[y + 2][x + 2] == o)) Total++;
            }
        }
    }
    return Total;
}

int main() {
    int N, M, Best = 0;
    cin >> N >> M;
    vector<string> Puzzle(N);
    for (int i = 0; i < N; i++) cin >> Puzzle[i];
    for (char m = 'A'; m <= 'Z'; m++) {
        for (char o = 'A'; o <= 'Z'; o++) {
            if ((m != 'M' and o != 'O') and m != o) Best = max(MostMoos(Puzzle, m, o, N, M), Best);
        }
    }
    cout << Best << "\n";
    return 0;
}
