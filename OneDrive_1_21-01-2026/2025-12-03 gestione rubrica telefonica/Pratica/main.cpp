#include <iostream>
#include <unordered_map>
using namespace std;

#include "Persona.h"


struct Hash_Persona{
    size_t operator()(const Persona& v)const{
        hash<string>{};
        size_t h1 = hash<string>{}(v.getNome());
        size_t h2 = hash<string>{}(v.getCognome());
        return h1 ^ (h2 << 1); // << 1 aggiunge un 1 alla fine della codifica (moltiplica per due)
    }
};

Persona leggiPersona();
void stampaMenu();
int main(){
    //mappa che associa ad ogni persona una stringa (n. di telefono) usando come hash la struct Hash_Persona
    unordered_map<Persona, string, Hash_Persona> rubrica;

    char scelta;
    do{
        stampaMenu();
        cin >> scelta;

        switch (scelta)
        {
            case '1':
            {
                Persona p; cin >> p;

                cout << "Inserisci n. di telefono -> ";
                string n_di_telefono; cin >> n_di_telefono;

                rubrica.insert({p, n_di_telefono});

                break;
            }
            case '2':
            {
        
                Persona p; cin >> p;

                if(rubrica.find(p) != rubrica.end())
                    cout << "Il numero di telefono di " << p.getNome() << " " << p.getCognome() << " e' " << rubrica[p] << endl;
                else
                    cout << "Contatto non presente in rubrica" << endl;

                break;
                
            }
            case '3':
            {
                Persona p; cin >> p;

                if(rubrica.erase(p))
                    cout << "Contatto eliminato" << endl;
                else 
                    cout << "Contatto non presente in rubrica" << endl;
            }
            case '4':
            {
                Persona p; cin >> p;
                if(rubrica.find(p) == rubrica.end())
                {
                    cout << "Contatto non presente" << endl;
                    break;
                }

                cout << "Inserisci il nuovo numero -> ";
                string n_di_telefono; cin >> n_di_telefono;
                rubrica[p] = n_di_telefono;

                break;

            }
            case '5':
            {
                Persona p; cin >> p;
                if(rubrica.find(p) == rubrica.end())
                {
                    cout << "Contatto non presente" << endl;
                    break;
                }
                string n_di_telefono = rubrica[p]; //salvo il numero
                rubrica.erase(p); //elimino la vecchia voce

                cout << "Inserisci i nuovi dati." << endl;
                cin >> p;

                rubrica.insert({p, n_di_telefono}); //inserisco i nuovi dati con lo stesso numero
                break;
            }

            case '6':
            {
                //it è un iteratore su oggetti di tipo pair
                for(auto it = rubrica.begin(); it != rubrica.end(); ++it){
                    cout << endl << it -> first; //chiave
                    cout << "Numero di telefono: " << it -> second << endl; //valore
    
                }

                break;
            }
            case '7':
            {
                cout << "Rubrica svuotata" << endl;
                break;
            }
            default:
                break;
        }
    }while(scelta != '0');

    return 0;
}

void stampaMenu(){
    cout << "Inserisci 1 per inserire un nuovo contatto." << endl;
    cout << "Inserisci 2 per cercare un contatto nella rubrica" << endl;
    cout << "Inserisci 3 per eliminare un contatto dalla rubrica" << endl;
    cout << "Inserisci 4 per modificare il numero di un contatto" << endl;
    cout << "Inserisci 5 per modificare nome/cognome di un contatto" << endl;
    cout << "Inserisci 6 per stampare la tua rubrica" << endl;
    cout << "Inserisci 7 per svuotare la rubrica" << endl;
    cout << "Inserisci 0 per uscire" << endl;
}