#include <iostream>
#include<list>
#include<map>
#include <vector>

using namespace std;

/*
class RegistroSpese{
    private:
        vector<double> spese;
    public:
        void aggiungiSpesa(double s){
            spese.push_back(s);
        }
        double calcolaTotale(){
            double tot = 0.0;
            for(int i = 0; i < spese.size(); i++){
                tot += spese[i];
            }
            return tot;
        }
}
*/

/*
class CodaOspedale{
    private: 
    list<string> pazienti;
    public:
    void arriva_paziente(const  string& nome){
        pazienti.push_back(nome);
    }
    void rimuovi_paziente(const string &nome){
        if(pazienti.empty()){
            return;
        }
        string removed = pazienti.front();
        pazienti.pop_front();
        return removed;
    }
    void stampa(){
        for(auto p:pazienti){
            cout<<p;
        }
        for(auto it = pazienti.begin(); it != pazienti.end(); it++){
            cout<<*it<<endl;
        }
    }
}

*/

class ContaParole {
    private: 
        map<string,int> frequenze;
    public:
        void aggiungi_parola(const string& parola){
            frequenze[parola] += 1;
        }
        int quante_volte(const string& parola) const {
            if(frequenze.find(parola) == frequenze.end()){
                return 0;
            }
            return frequenze.at(parola);
        }
};

class contaParole {
    private:
        map<string, pair<int, string>> frequenze; // parola, (numero, giorno)
    public:
        void aggiungi_parola(const string& parola, const string& giorno){
            frequenze[parola].first += 1;
            frequenze[parola].second = giorno;
        }

        int quante_volte(const string& parola) const {
            if (frequenze.find(parola) == frequenze.end()) {
                return 0;
            }
            return frequenze.at(parola).first;
        }

        string ultimo_giorno(const string& parola) const {
            if (frequenze.find(parola) == frequenze.end()) {
                return "";
            }
            return frequenze.at(parola).second;
        }

        pair<int, string> trova(const string& parola) const {
            if (frequenze.find(parola) == frequenze.end()) {
                return {0, ""};
            }
            return frequenze.at(parola);
        }

        void stampa() const {
            for (const auto& entry : frequenze) {
                cout << "Parola: " << entry.first 
                     << " | Frequenza: " << entry.second.first 
                     << " | Ultimo giorno: " << entry.second.second << endl;
            }
        }
};

class RegistroPresenze {
    private:
        // Mappa nidificata: giorno -> (ora -> (età_media, nomi))
        map<string, map<string, pair<double, vector<string>>>> dati;

    public:
        // Aggiunge una persona calcolando la nuova età media in tempo reale
        void aggiungi_persona(const string& giorno, const string& ora, const string& nome, int eta) {
            auto& info = dati[giorno][ora]; // Riferimento al pair<double, vector<string>>
            double eta_media_attuale = info.first;
            size_t n = info.second.size();
            
            // Formula dell'età media incrementale:
            // nuova_media = ((vecchia_media * n) + nuova_eta) / (n + 1)
            double nuova_eta_media = ((eta_media_attuale * n) + eta) / (n + 1);
            
            info.first = nuova_eta_media;
            info.second.push_back(nome);
        }

        // Restituisce le informazioni per giorno e ora usando .at() (in sola lettura)
        pair<double, vector<string>> ottieni_info(const string& giorno, const string& ora) const {
            if (dati.find(giorno) == dati.end() || dati.at(giorno).find(ora) == dati.at(giorno).end()) {
                return {0.0, {}};
            }
            return dati.at(giorno).at(ora);
        }

        // Stampa tutto il registro presenze
        void stampa() const {
            for (const auto& entry_giorno : dati) {
                cout << "Giorno: " << entry_giorno.first << endl;
                for (const auto& entry_ora : entry_giorno.second) {
                    cout << "  Ora: " << entry_ora.first 
                         << " | Eta' Media: " << entry_ora.second.first 
                         << " | Nomi: ";
                    for (const auto& nome : entry_ora.second.second) {
                        cout << nome << " ";
                    }
                    cout << endl;
                }
            }
        }
};

class Studente{
    private:
        string nome;
        int mat;
    public:
        Studente(string n,int m){
            nome = n;
            mat = m;
        }
        Studente(string n,int m): nome(n), mat(m){}
        
}