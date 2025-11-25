#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Studente {
private:
    int matricola;
    double isee;
    double media;

public:
    Studente(int m, double i, double med) : matricola(m), isee(i), media(med) {}

    int getMatricola() const { return matricola; }
    double getIsee() const { return isee; }
    double getMedia() const { return media; }

    // Overload operator<< for easy printing
    friend ostream& operator<<(ostream& os, const Studente& s) {
        os << "Matricola: " << s.matricola << ", Media: " << s.media << ", ISEE: " << s.isee;
        return os;
    }
};

class CodaEreditaria : private vector<Studente> {
public:
    void aggiungi(Studente s) {
        for (const auto& existing : *this) {
            if (existing.getMatricola() == s.getMatricola()) {
                return; // Already exists
            }
        }
        push_back(s);
    }

    // Helper to find the index of the "next" student
    int findNextIndex() const {
        if (empty()) return -1;

        int bestIndex = -1;
        
        // We need to find the best candidate based on the rules.
        // Since we need to iterate anyway, let's just pick the best one.
        
        // Rules:
        // 1. Media > 28 (FIFO)
        // 2. 26 <= Media <= 28 (Min Matricola)
        // 3. Media < 26 (Min ISEE)

        // Strategy:
        // We can categorize each student into a priority tier:
        // Tier 1: Media > 28
        // Tier 2: 26 <= Media <= 28
        // Tier 3: Media < 26
        
        // We want the student in the highest available tier.
        // Within Tier 1: The one with the lowest index (FIFO).
        // Within Tier 2: The one with the lowest matricola.
        // Within Tier 3: The one with the lowest ISEE.

        int currentBestTier = 4; // Start worse than any real tier

        for (size_t i = 0; i < size(); ++i) {
            const Studente& s = at(i);
            int tier;
            if (s.getMedia() > 28) tier = 1;
            else if (s.getMedia() >= 26) tier = 2;
            else tier = 3;

            if (tier < currentBestTier) {
                currentBestTier = tier;
                bestIndex = i;
            } else if (tier == currentBestTier) {
                const Studente& best = at(bestIndex);
                if (tier == 1) {
                    // FIFO: keep the existing bestIndex (since i > bestIndex)
                } else if (tier == 2) {
                    // Min Matricola
                    if (s.getMatricola() < best.getMatricola()) {
                        bestIndex = i;
                    }
                } else if (tier == 3) {
                    // Min ISEE
                    if (s.getIsee() < best.getIsee()) {
                        bestIndex = i;
                    }
                }
            }
        }
        return bestIndex;
    }

    Studente prossimo() const {
        int idx = findNextIndex();
        if (idx == -1) {
            throw runtime_error("Coda vuota");
        }
        return at(idx);
    }

    void rimuovi() {
        int idx = findNextIndex();
        if (idx != -1) {
            erase(begin() + idx);
        }
    }

    unsigned int size() const {
        return vector<Studente>::size();
    }
    
    bool empty() const {
        return vector<Studente>::empty();
    }
};

int main() {
    CodaEreditaria coda;

    // Test Data
    Studente s1(101, 20000, 29); // Tier 1 (FIFO 1)
    Studente s2(102, 15000, 25); // Tier 3
    Studente s3(103, 30000, 27); // Tier 2
    Studente s4(104, 10000, 30); // Tier 1 (FIFO 2)
    Studente s5(100, 25000, 27); // Tier 2 (Lower matricola than s3)
    Studente s6(105, 5000, 24);  // Tier 3 (Lower ISEE than s2)
    Studente s7(101, 99999, 18); // Duplicate matricola, should be ignored

    cout << "Aggiungo studenti..." << endl;
    coda.aggiungi(s1);
    coda.aggiungi(s2);
    coda.aggiungi(s3);
    coda.aggiungi(s4);
    coda.aggiungi(s5);
    coda.aggiungi(s6);
    coda.aggiungi(s7); // Duplicate

    cout << "Dimensione coda: " << coda.size() << " (Atteso: 6)" << endl;

    // Expected Order:
    // 1. s1 (Media 29 > 28, arrived first)
    // 2. s4 (Media 30 > 28, arrived second)
    // 3. s5 (Media 27, Tier 2, Matricola 100 < 103)
    // 4. s3 (Media 27, Tier 2, Matricola 103)
    // 5. s6 (Media 24, Tier 3, ISEE 5000 < 15000)
    // 6. s2 (Media 25, Tier 3, ISEE 15000)

    cout << "\nEstrazione:" << endl;
    while (coda.size() > 0) {
        Studente next = coda.prossimo();
        cout << next << endl;
        coda.rimuovi();
    }

    return 0;
}

