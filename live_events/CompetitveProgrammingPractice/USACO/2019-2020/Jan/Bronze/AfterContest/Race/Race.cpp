#include <fstream>

using namespace std;

ofstream fout("race.out");
ifstream fin("race.in");

int MinRaceTime(int K, int X) {
    int Time = 0, Dist = 0, Spd = 0;
    while (Dist < K) {
        Spd++;
        for (int i = 0; i < 2; i++) {
            if (Spd > X) {
                int n = Spd - X;
                if (n * X + (n * (n + 1) / 2) >= K - Dist) Spd--;
            }
        }
        Time++;
        Dist += Spd;
    }
    return Time;
}

int main() {
    int K, N, X;
    fin >> K >> N;
    for (int i = 0; i < N; i++) {
        fin >> X;
        fout << MinRaceTime(K, X) << "\n";
    }
    return 0;
}
