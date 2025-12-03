#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Persona {
private:
    string nome;
    string cognome;
    string numero;

public:
    // Costruttore di default
    Persona() {}

    // Costruttore con parametri
    Persona(string n, string c, string num) : nome(n), cognome(c), numero(num) {}

    // Getters
    string getNome() const { return nome; }
    string getCognome() const { return cognome; }
    string getNumero() const { return numero; }

    // Setters
    void setNome(string n) { nome = n; }
    void setCognome(string c) { cognome = c; }
    void setNumero(string num) { numero = num; }

    // Operatore di input >>
    friend istream& operator>>(istream& is, Persona& p) {
        cout << "Inserisci nome: ";
        is >> p.nome;
        cout << "Inserisci cognome: ";
        is >> p.cognome;
        cout << "Inserisci numero: ";
        is >> p.numero;
        return is;
    }

    // Operatore di output <<
    friend ostream& operator<<(ostream& os, const Persona& p) {
        os << "Nome: " << p.nome << ", Cognome: " << p.cognome << ", Numero: " << p.numero;
        return os;
    }
};

// Funzione per cercare un contatto
int cercaContatto(const vector<Persona>& rubrica, string nome, string cognome) {
    for (size_t i = 0; i < rubrica.size(); ++i) {
        if (rubrica[i].getNome() == nome && rubrica[i].getCognome() == cognome) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<Persona> rubrica;
    int scelta;

    do {
        cout << "\n--- GESTIONE RUBRICA ---\n";
        cout << "1. Inserisci nuovo contatto\n";
        cout << "2. Cerca contatto\n";
        cout << "3. Elimina contatto\n";
        cout << "4. Modifica numero contatto\n";
        cout << "5. Modifica nome e cognome contatto\n";
        cout << "6. Stampa rubrica\n";
        cout << "7. Svuota rubrica\n";
        cout << "0. Esci\n";
        cout << "Scelta: ";
        
        if (!(cin >> scelta)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            scelta = -1; 
        }

        string nome, cognome, nuovoNumero, nuovoNome, nuovoCognome;
        int index;
        Persona p;

        switch (scelta) {
            case 1: // Inserisci
                cin >> p;
                if (cercaContatto(rubrica, p.getNome(), p.getCognome()) != -1) {
                    cout << "Errore: Contatto gia' esistente!\n";
                } else {
                    rubrica.push_back(p);
                    cout << "Contatto inserito con successo.\n";
                }
                break;

            case 2: // Cerca
                cout << "Inserisci nome da cercare: ";
                cin >> nome;
                cout << "Inserisci cognome da cercare: ";
                cin >> cognome;
                index = cercaContatto(rubrica, nome, cognome);
                if (index != -1) {
                    cout << "Contatto trovato: " << rubrica[index] << endl;
                } else {
                    cout << "Contatto non trovato.\n";
                }
                break;

            case 3: // Elimina
                cout << "Inserisci nome da eliminare: ";
                cin >> nome;
                cout << "Inserisci cognome da eliminare: ";
                cin >> cognome;
                index = cercaContatto(rubrica, nome, cognome);
                if (index != -1) {
                    rubrica.erase(rubrica.begin() + index);
                    cout << "Contatto eliminato.\n";
                } else {
                    cout << "Contatto non trovato.\n";
                }
                break;

            case 4: // Modifica numero
                cout << "Inserisci nome del contatto: ";
                cin >> nome;
                cout << "Inserisci cognome del contatto: ";
                cin >> cognome;
                index = cercaContatto(rubrica, nome, cognome);
                if (index != -1) {
                    cout << "Inserisci nuovo numero: ";
                    cin >> nuovoNumero;
                    rubrica[index].setNumero(nuovoNumero);
                    cout << "Numero aggiornato.\n";
                } else {
                    cout << "Contatto non trovato.\n";
                }
                break;

            case 5: // Modifica nome e cognome
                cout << "Inserisci nome attuale: ";
                cin >> nome;
                cout << "Inserisci cognome attuale: ";
                cin >> cognome;
                index = cercaContatto(rubrica, nome, cognome);
                if (index != -1) {
                    cout << "Inserisci nuovo nome: ";
                    cin >> nuovoNome;
                    cout << "Inserisci nuovo cognome: ";
                    cin >> nuovoCognome;
                    
                    // Verifica se il nuovo nome/cognome esiste gia' (se diverso dall'attuale)
                    if ((nuovoNome != nome || nuovoCognome != cognome) && 
                        cercaContatto(rubrica, nuovoNome, nuovoCognome) != -1) {
                        cout << "Errore: Esiste gia' un contatto con questo nuovo nome e cognome.\n";
                    } else {
                        rubrica[index].setNome(nuovoNome);
                        rubrica[index].setCognome(nuovoCognome);
                        cout << "Nome e cognome aggiornati.\n";
                    }
                } else {
                    cout << "Contatto non trovato.\n";
                }
                break;

            case 6: // Stampa
                if (rubrica.empty()) {
                    cout << "Rubrica vuota.\n";
                } else {
                    cout << "\n--- ELENCO CONTATTI ---\n";
                    for (const auto& persona : rubrica) {
                        cout << persona << endl;
                    }
                }
                break;

            case 7: // Svuota
                rubrica.clear();
                cout << "Rubrica svuotata.\n";
                break;

            case 0: // Esci
                cout << "Arrivederci!\n";
                break;

            default:
                cout << "Scelta non valida.\n";
        }

    } while (scelta != 0);

    return 0;
}
