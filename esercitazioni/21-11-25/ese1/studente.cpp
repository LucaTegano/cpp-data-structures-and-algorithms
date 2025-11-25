#include "studente.h"
#include <algorithm> // Per max

// Costruttore di default
StudenteDinamico::StudenteDinamico() : matricola(0), nascita() {
    voti = new int[25];
    for (int i = 0; i < 25; ++i) {
        voti[i] = 0;
    }
}

// Costruttore di copia
StudenteDinamico::StudenteDinamico(const StudenteDinamico& other) : matricola(other.matricola), nascita(other.nascita) {
    voti = new int[25];
    for (int i = 0; i < 25; ++i) {
        voti[i] = other.voti[i];
    }
}

// Distruttore
StudenteDinamico::~StudenteDinamico() {
    delete[] voti;
}

// Operatore di assegnamento
StudenteDinamico& StudenteDinamico::operator=(const StudenteDinamico& other) {
    if (this != &other) {
        matricola = other.matricola;
        nascita = other.nascita;
        delete[] voti;
        voti = new int[25];
        for (int i = 0; i < 25; ++i) {
            voti[i] = other.voti[i];
        }
    }
    return *this;
}

// Setters
void StudenteDinamico::setMatricola(int m) {
    matricola = m;
}

void StudenteDinamico::setNascita(const Data& d) {
    nascita = d;
}

void StudenteDinamico::setVoto(int indice, int voto) {
    if (indice >= 0 && indice < 25) {
        voti[indice] = voto;
    }
}

// Getters
int StudenteDinamico::getMatricola() const {
    return matricola;
}

Data StudenteDinamico::getNascita() const {
    return nascita;
}

int StudenteDinamico::getVoto(int indice) const {
    if (indice >= 0 && indice < 25) {
        return voti[indice];
    }
    return -1; // Errore
}

// Metodi richiesti
double StudenteDinamico::getMedia() const {
    double somma = 0;
    int cont = 0;
    for (int i = 0; i < 25; ++i) {
        if (voti[i] >= 18 && voti[i] <= 30) { // Consideriamo solo esami superati per la media? O anche bocciati?
            // Il testo dice "media dei voti dello studente". Di solito si intende media esami superati.
            // Ma dice anche "Voti da 1 a 17 per esami sostenuti ma non superati".
            // Assumiamo media di tutti gli esami SOSTENUTI (voto > 0).
            if (voti[i] > 0) {
                somma += voti[i];
                cont++;
            }
        }
    }
    if (cont == 0) return 0.0;
    return somma / cont;
}

int StudenteDinamico::getVotoMax() const {
    int maxVoto = 0;
    for (int i = 0; i < 25; ++i) {
        if (voti[i] > maxVoto) {
            maxVoto = voti[i];
        }
    }
    return maxVoto;
}

int StudenteDinamico::getNumEsamiAllaLaurea() const {
    int esamiMancanti = 0;
    for (int i = 0; i < 25; ++i) {
        if (voti[i] < 18) { // Esami non superati o non sostenuti
            esamiMancanti++;
        }
    }
    return esamiMancanti;
}

bool StudenteDinamico::studentePiuGiovaneDi(const StudenteDinamico& S) const {
    // Se *this è più giovane, la sua data di nascita è "maggiore" (più recente) di S.nascita
    // Data::operator< controlla se è "minore" (più vecchia).
    // Quindi *this > S.nascita => !(*this < S.nascita) && !(*this == S.nascita)
    // Oppure semplicemente implementiamo la logica inversa.
    // Data A < Data B significa A è prima di B (A è più vecchio).
    // Quindi se NascitaA > NascitaB, A è più giovane.
    return S.nascita < nascita;
}

// Input/Output
ostream& operator<<(ostream& os, const StudenteDinamico& s) {
    os << "Matricola: " << s.matricola << ", Nascita: " << s.nascita << "\nVoti: ";
    for (int i = 0; i < 25; ++i) {
        os << s.voti[i] << " ";
    }
    return os;
}

istream& operator>>(istream& is, StudenteDinamico& s) {
    cout << "Inserisci matricola: ";
    is >> s.matricola;
    cout << "Inserisci data di nascita (g/m/a): ";
    is >> s.nascita;
    cout << "Inserisci 25 voti (0 per non sostenuto, 1-17 bocciato, 18-30 superato):" << endl;
    for (int i = 0; i < 25; ++i) {
        is >> s.voti[i];
    }
    return is;
}