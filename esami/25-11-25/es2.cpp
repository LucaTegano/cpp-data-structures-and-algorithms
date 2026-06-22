#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class rotcev : private vector<int> {
public:
    // Unico costruttore pubblico richiesto
    rotcev() : vector<int>() {}

    // Ridefinizione dei metodi pubblici richiesti:

    // 1. operator[] che restituisce l'i-esimo elemento a partire da destra
    int& operator[](int i) {
        return vector<int>::operator[](vector<int>::size() - 1 - i);
    }

    // 2. push_back che si comporta esattamente come in vector<int>
    void push_back(int value) {
        vector<int>::push_back(value);
    }

    // 3. front che restituisce l'ultimo elemento del vector (il primo a destra)
    int front() const {
        return vector<int>::back();
    }

    // 4. back che restituisce il primo elemento del vector (l'ultimo a destra)
    int back() const {
        return vector<int>::front();
    }

    // 5. size che si comporta esattamente come in vector<int>
    unsigned size() const {
        return vector<int>::size();
    }
};

// Classe di test per verificare che le classi derivate non abbiano accesso
// ai metodi di vector<int>, neanche all'interno delle loro definizioni.
class DerivedFromRotcev : public rotcev {
public:
    void testAccessRestrictions() {
        // Le seguenti righe causerebbero errori di compilazione se decommentate:
        // this->clear();                  // ERRORE: 'clear' è privato/inaccessibile
        // this->pop_back();               // ERRORE: 'pop_back' è privato/inaccessibile
        // int x = vector<int>::size();    // ERRORE: 'vector<int>' è una base privata
    }
};

int main() {
    cout << "=== Avvio dei Test per la classe rotcev ===" << endl;

    rotcev r;

    // Test push_back e size
    r.push_back(10);
    r.push_back(20);
    r.push_back(30);
    r.push_back(40);

    cout << "Size dopo 4 push_back: " << r.size() << " (Atteso: 4)" << endl;
    assert(r.size() == 4);

    // Test operator[] (indicizzazione da destra)
    // Elementi: [10, 20, 30, 40]
    // Indici da destra: r[0] = 40, r[1] = 30, r[2] = 20, r[3] = 10
    cout << "r[0]: " << r[0] << " (Atteso: 40)" << endl;
    cout << "r[1]: " << r[1] << " (Atteso: 30)" << endl;
    cout << "r[2]: " << r[2] << " (Atteso: 20)" << endl;
    cout << "r[3]: " << r[3] << " (Atteso: 10)" << endl;

    assert(r[0] == 40);
    assert(r[1] == 30);
    assert(r[2] == 20);
    assert(r[3] == 10);

    // Test di modifica tramite operator[]
    r[1] = 35; // Modifica l'elemento 30 -> 35
    cout << "Modificato r[1] = 35. Nuovo valore r[1]: " << r[1] << " (Atteso: 35)" << endl;
    assert(r[1] == 35);

    // Test front e back
    // Elementi nel vector: [10, 20, 35, 40]
    // front() deve restituire l'ultimo elemento (40)
    // back() deve restituire il primo elemento (10)
    cout << "front() (ultimo elemento): " << r.front() << " (Atteso: 40)" << endl;
    cout << "back() (primo elemento): " << r.back() << " (Atteso: 10)" << endl;

    assert(r.front() == 40);
    assert(r.back() == 10);

    // I seguenti test di compilazione (se scommentati) fallirebbero confermando le restrizioni:
    // r.clear();                      // ERRORE: clear() non è pubblico
    // vector<int>* pv = &r;           // ERRORE: conversione a base privata non consentita
    // vector<int>& rv = r;            // ERRORE: conversione a base privata non consentita

    cout << "=== Tutti i test sono passati con successo! ===" << endl;
    return 0;
}
