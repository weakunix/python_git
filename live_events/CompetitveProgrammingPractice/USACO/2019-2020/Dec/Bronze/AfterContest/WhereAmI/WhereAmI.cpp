#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

ofstream fout("whereami.out");
ifstream fin("whereami.in");

int main() {
    int N;
    string Mailboxes, CurSection;
    unordered_set<string> Sections;
    bool Works;
    fin >> N >> Mailboxes;
    for (int K = 1; K <= N; K++) {
        Sections.clear();
        Works = true;
        for (int i = 0; i <= N - K; i++) {
            CurSection = Mailboxes.substr(i, K);
            if (Sections.count(CurSection) > 0) {
                Works = false;
                break;
            }
            Sections.insert(CurSection);
        }
        if (Works) {
            fout << K << "\n";
            return 0;
        }
    }
}
