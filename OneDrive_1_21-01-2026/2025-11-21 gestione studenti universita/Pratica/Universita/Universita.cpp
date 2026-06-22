#include "Universita.h"

// Costruttore di default
// Inizializziamo con una capacity piccola (es. 5) per evitare subito resize
Universita::Universita() 
    : nome("Senza Nome"), numeroStudenti(0), capacity(5) {
    studenti = new StudenteDinamico[capacity];
}

// Costruttore parametrizzato
Universita::Universita(string nome) 
    : nome(nome), numeroStudenti(0), capacity(5) {
    studenti = new StudenteDinamico[capacity];
}

// Costruttore di Copia
Universita::Universita(const Universita& other) 
    : nome(other.nome), numeroStudenti(other.numeroStudenti), capacity(other.capacity) {
    
    // Allochiamo in base alla capacity dell'altro, non solo al numero studenti
    studenti = new StudenteDinamico[capacity];
    for (int i = 0; i < numeroStudenti; ++i) {
        studenti[i] = other.studenti[i];
    }
}

// Distruttore
Universita::~Universita() {
    delete[] studenti;
}

// Operatore di Assegnamento
Universita& Universita::operator=(const Universita& other) {
    if (this == &other) return *this;

    delete[] studenti;

    nome = other.nome;
    numeroStudenti = other.numeroStudenti;
    capacity = other.capacity;

    studenti = new StudenteDinamico[capacity];
    for (int i = 0; i < numeroStudenti; ++i) {
        studenti[i] = other.studenti[i];
    }

    return *this;
}

// Metodo privato per gestire l'espansione di memoria
void Universita::ridimensiona(int nuovaCapacity) {
    // 1. Crea nuovo array più grande
    StudenteDinamico* temp = new StudenteDinamico[nuovaCapacity];

    // 2. Copia i dati esistenti
    for (int i = 0; i < numeroStudenti; ++i) {
        temp[i] = studenti[i];
    }

    // 3. Dealloca vecchia memoria
    delete[] studenti;

    // 4. Aggiorna puntatore e capacity
    studenti = temp;
    capacity = nuovaCapacity;
    
    // Opzionale: Debug per vedere quando avviene il raddoppio
    cout << "[DEBUG] Array ridimensionato. Nuova capacity: " << capacity << endl;
}

// Aggiungi studente 
void Universita::aggiungiStudente(const StudenteDinamico& s) {
    // Se l'array è pieno, raddoppia la capacità
    if (numeroStudenti == capacity) {
        //ATTENZIONE, funziona perchè capacity di default è 5. se inizializzata a 0 va fatto il controllo prima della moltiplicazione
        int nuovaCap = capacity * 2;
        ridimensiona(nuovaCap);
    }

    // Inserimento diretto (nessuna allocazione qui)
    studenti[numeroStudenti] = s;
    numeroStudenti++;
}

// Rimuovi studente (Shifting senza deallocazione)
bool Universita::rimuoviStudente(int matricola) {
    int index = cercaStudente(matricola);
    if (index == -1) return false; 

    // Spostiamo tutti gli elementi successivi indietro di una posizione
    // per coprire il buco lasciato dallo studente rimosso.
    for (int i = index; i < numeroStudenti - 1; ++i) {
        studenti[i] = studenti[i + 1];
    }

    // Decrementiamo solo il contatore logico.
    // La memoria fisica (capacity) resta allocata per futuri inserimenti e lo studente che c'era prima in quella posizione verrà sovrascritto
    numeroStudenti--;
    
    return true;
}

int Universita::cercaStudente(int matricola) const {
    for (int i = 0; i < numeroStudenti; ++i) {
        if (studenti[i].getMatricola() == matricola) {
            return i;
        }
    }
    return -1;
}

StudenteDinamico& Universita::getStudente(int matricola) {
    int index = cercaStudente(matricola);
    if (index != -1) return studenti[index];
    
    cout << "ERRORE: Studente non trovato!" << endl;
    return studenti[0]; 
}

void Universita::setStudente(int matricola, const StudenteDinamico& s) {
    int index = cercaStudente(matricola);
    if (index != -1) {
        studenti[index] = s;
    } else {
        cout << "ERRORE: Matricola inesistente." << endl;
    }
}

StudenteDinamico Universita::migliorStudente() const {
    if (numeroStudenti == 0) return StudenteDinamico();

    int idxBest = 0;
    float maxMedia = studenti[0].getMedia();

    for (int i = 1; i < numeroStudenti; ++i) {
        float mediaCorr = studenti[i].getMedia();
        if (mediaCorr > maxMedia) {
            maxMedia = mediaCorr;
            idxBest = i;
        }
    }
    return studenti[idxBest];
}

ostream& operator<<(ostream& out, const Universita& u) {
    out << "=== UNIVERSITA: " << u.nome << " ===" << endl;
    out << "Studenti: " << u.numeroStudenti << " / Capacity: " << u.capacity << endl;
    out << "-----------------------------" << endl;
    for (int i = 0; i < u.numeroStudenti; ++i) {
        out << "Posizione [" << i << "]: " << endl;
        out << u.studenti[i] << endl;
    }
    return out;
}