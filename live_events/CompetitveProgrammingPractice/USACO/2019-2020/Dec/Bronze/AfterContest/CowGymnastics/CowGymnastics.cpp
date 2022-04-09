/*
Test outputs

1:
4
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream fout("gymnastics.out");
ifstream fin("gymnastics.in");

int main() {

    //Vars
    int K, N, Ranking, TotalConsistent = 0;
    vector<vector<int> > Practices;
    
    //Temp vars
    int temp_int;
    vector<int> temp_vect_int;

    fin >> K >> N;
    for (int i = 0; i < K; i++) {
        temp_vect_int.clear();
        for (int k = 0; k < N; k++) {
            fin >> temp_int;
            temp_vect_int.push_back(temp_int);
        }
        Practices.push_back(temp_vect_int);
    }
    for (int i = 1; i < N; i++) {
        for (int k = i + 1; k <= N; k++) {
            Ranking = 0;
            for (vector<int> v : Practices) {
                if (Ranking == 0) {
                    if (find(v.begin(), v.end(), i) < find(v.begin(), v.end(), k))
                        Ranking = 1;
                    else
                        Ranking = 2;
                }
                else if ((find(v.begin(), v.end(), i) < find(v.begin(), v.end(), k) and Ranking == 2) or (find(v.begin(), v.end(), i) > find(v.begin(), v.end(), k) and Ranking == 1)) {
                    Ranking = -1;
                    break;
                }
            }
            if (Ranking > 0)
                TotalConsistent += 1;
        }
    }
    fout << TotalConsistent << "\n";
    return 0;
}
