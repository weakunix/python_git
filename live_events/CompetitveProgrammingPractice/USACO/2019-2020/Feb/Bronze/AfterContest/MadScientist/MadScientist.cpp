#include <fstream>
#include <string>

using namespace std;

ofstream fout("breedflip.out");
ifstream fin("breedflip.in");

int main() {
    int N, Flips = 0;
    bool Dif = false;
    string A, B;
    fin >> N >> A >> B;
    for (int i = 0; i < N; i++) {
        if (A[i] == B[i]) Dif = false;
        else if (not Dif) {
            Flips++;
            Dif = true;
        }
    }
    fout << Flips << "\n";
    return 0;
}
