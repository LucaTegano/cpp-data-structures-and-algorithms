/*Esercizio 1: Progettare e implementare una classe Concessionaria tenendo
conto delle seguenti specifiche:
• La concessionaria pu`o contenere due tipologie di veicoli: Automobili e
Moto. Utilizzare l’ereditariet`a, creando la classe Veicolo, per generalizzare
le classi Automobile e Moto.
• Ogni veicolo contiene le informazioni riguardanti la targa, il prezzo, la
casa produttrice ed il nome del veicolo. La targa del veicolo deve essere
univoca per ogni veicolo.
• Deve essere presente un metodo che restituisca il prezzo scontato, calcolato
come segue:
– Per le automobili con un prezzo inferiore ai 10000 euro, lo sconto `e
del 5%
– Per le automobili con un prezzo inferiore ai 20000 euro, lo sconto `e
del 10%
– Per le moto con un prezzo inferiore ai 7000 euro, lo sconto `e del 3%
– Per le moto con un prezzo inferiore ai 15000 euro, lo sconto `e del
7.5%
– Negli altri casi il prezzo non `e scontato
• Deve essere possibile aggiungere e rimuovere un veicolo dal concessionario.
• Deve essere possibile stampare, utilizzando l’operatore << di Veicolo, tutti
i veicoli presenti.
Progettare e implementare una classe GestoreVeicoli che si occupi di gestire i
veicoli da aggiungere alla concessionaria.
Inoltre, implementare il seguente men`u:
Premi 1 per aggiungere un’automobile al gestore veicoli
Premi 2 per aggiungere una moto al gestore veicoli
Premi 3 per aggiungere un veicolo del gestore veicoli alla concessionaria (usando
la targa)
Premi 4 per rimuovere un veicolo dalla concessionaria (usando la targa)
Premi 5 per stampare il prezzo scontato di un veicolo (usando la targa)
Premi 6 per stampare tutti i veicoli presenti nella concessionaria
Premi 9 per uscire*/

#include <iostream>
#include <string>

using namespace std;
class Veicolo{
 private:
    string targa;
    double prezzo;
    string casaProduttrice;
    string nomeVeicolo;
public:
    Veicolo() = default;
    Veicolo(string targa, double prezzo, string casaProduttrice, string nomeVeicolo){
        this->targa=targa;
        this->prezzo=prezzo;
        this->casaProduttrice=casaProduttrice;
        this->nomeVeicolo=nomeVeicolo;
    }
    virtual ~Veicolo(){};
    string getTarga(){return targa;}
    virtual double getPrezzo(){return prezzo;}
    string getCasaProduttrice(){return casaProduttrice;}
    string getNomeVeicolo(){return nomeVeicolo;}
    void setTarga(string targa){this->targa=targa;}
    void setPrezzo(double prezzo){this->prezzo=prezzo;}
    void setCasaProduttrice(string casaProduttrice){this->casaProduttrice=casaProduttrice;}
    void setNomeVeicolo(string nomeVeicolo){this->nomeVeicolo=nomeVeicolo;}

    virtual Veicolo* clone() {
        return new Veicolo(*this);
    };
}

class Automobile : public Veicolo{
public:
    Automobile() = default;
    Automobile(string targa, double prezzo, string casaProduttrice, string nomeVeicolo){
        this->targa=targa;
        this->prezzo=prezzo;
        this->casaProduttrice=casaProduttrice;
        this->nomeVeicolo=nomeVeicolo;
    }
    double getPrezzo() const {
        double p = Veicolo::getPrezzo();
        if(p < 10000)
            return p - (p*0.05)
        if(p<20000)
            return p - (p*0.1);
        return p;
    }
    Automobile* clone() {
        return new Automobile(*this);
    }
}; 

class Moto: public Veicolo {
    public:
        double getPrezzo() const {
        double p = Veicolo::getPrezzo();
        if(p < 7000)
            return p - (p*0.03)
        if(p<15000)
            return p - (p*0.075);
        return p;
        
        friend ostream& operator<<(ostream&os , const Veicolo&v ){
            os<< v.targa<<< ' '<< v.getPrezzo()<< ' ' << v.casa_produttrice << ' '<< v.nome<<endl
        }
    }
    Moto* clone() {
        return new Moto(*this);
    }
};

class Concessionaria {
    private:
        vector<Veicolo*> veicoli;
    public:
        Concessionaria(): veicoli({}){}
        vector<Veicoli*> getVeicoli() const {return veicoli;    }
        bool aggiungi(Veicolo* v){
            for(auto it = veicoli.begin(); it != veicoli.end(); ++it)
            if((*it) -> getTarga() == v->getTarga()){
                cout<<"Impossibile aggiungere il veicolo: targa già esistente"<<endl;
                return false;
            }
        };
        bool rimuovi(const string & targa) {
            for(auto it =veicoli.begin(); it != veicoli.end();++it)
                if((*it) -> getTarga() == targa) {
                    cout<<"Veicolo rimosso con successo" <<endl;
                    veicoli.esase(it);
                    return true;
                }
            cout << "Impossibile aggiungere il veicolo: targa inesistente" << endl;
            return false;
        }
};
class GestoreVeicoli {
    private: 
        vector<Veicolo * > veicoli;
        void aggiungiVeicolo(Veicolo* v) {
            for(Veicolo* veicolo: veicoli)
                if(veicolo-> getTarga() == v -> getTarga()){
                    cout<<"Impossibile aggiungere il veicolo: targa già esistente"<<endl;
                    return;
                }
            veicoli.push_back(v);
            cout<<"Veicolo aggiunto con successo"<<endl;
        }
        void clear(){
            for(Veicolo* v: veicoli)
                delete v;
            veicoli.clear();
        }
    public:
        GestoreVeicoli(){}

        void aggiungiAutomobile(string t, double p, string c , string n) {
            Veicolo* a = new Automobile(t,p,c,n);
            aggiungiVeicolo(a);
        }

        void agginungiMoto(string t, double p, string c , string n) {
            Veicolo* m = new Moto(t,p,c,n);
            aggiungiVeicolo(m);
        }
        ~GestoreVeicoli(){
            clear();
        }
        GestoreVeicoli &operator=(const GestoreVeicoli &g){
            if(this != &g){
                clear();
                for(Veicolo* v: g.veicoli)
                    aggiungiVeicolo(v);
            }
            return *this;
        }
        GestoreVeicoli(const GestoreVeicoli &g){
            for(Veicolo* v: g.veicoli)
                aggiungiVeicolo(v->clone());
        }
        
};

void stampaMenu() {
    cout << "1 per aggiungere un’automobile al gestore veicoli"<<endl;
    << "9 per uscire"<<endl;
}

int main() {
    int choice;
    cin >> choice;
    
    while(choice != 9) {
        switch (choice) {
            case 1: {
                string t,c,c;
                float p;
                cout << "Inserisci targa, prezzo, casa produttrice e nome separati da spazi: ";
                cin >> t >> p >> c >> n;
                g.aggiungiAutomobile(t,p,c,n);
                break;
            }
            case 2: {
                string t,c,c;
                float p;
                cout << "Inserisci targa, prezzo, casa produttrice e nome separati da spazi: ";
                cin >> t >> p >> c >> n;
                g.aggiungiMoto(t,p,c,n);
                break;
            }
            case 3: {
                string t;
                cout << "Inserisci targa: ";
                cin >> t;
                g.aggiungiVeicolo(t);
                break;
            }
            case 4: {
                string t;
                cout << "Inserisci targa: ";
                cin >> t;
                g.rimuoviVeicolo(t);
                break;
            }
            case 5: {
                string t;
                cout << "Inserisci targa: ";
                cin >> t;
                cout << g.getPrezzoScontato(t) << endl;
                break;
            }
            case 6: {
                g.stampaVeicoli();
                break;
            }
            default: {
                cout<<"Input non valido"<<endl;
                break;
            }
        }
        cin >> choice;
    }
    return 0;
}//QUANDO MANIPOLO DINAMICA COSTRUTTORE PER COPIA ,OPERATORE DI ASSEGNAMENTO , E DISTRUTTORE