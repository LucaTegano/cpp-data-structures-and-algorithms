#include <iostream>
#include <vector>

using namespace std;

int analizzaDati(const vector<int>& dati) {
    int contatorePicchi = 0;

    if (dati.size() < 3) {
        return 0;
    }

    for (size_t i = 1; i < dati.size() - 1; ++i) {
        if (dati[i] > dati[i - 1] && dati[i] > dati[i + 1]) {
            cout << dati[i] << " " << i + 1 << endl;
            contatorePicchi++;
        }
    }

    return contatorePicchi;
}

int main() {
    vector<int> tassiInquinamento;
    int valore;

    while (cin >> valore && valore >= 0) {
        tassiInquinamento.push_back(valore);
    }

    int numeroPicchi = analizzaDati(tassiInquinamento);

    cout << "Numero di picchi massimi rilevati: " << numeroPicchi << endl;
    cout << "Numero totale dei dati: " << tassiInquinamento.size() << endl;

    return 0;
}
