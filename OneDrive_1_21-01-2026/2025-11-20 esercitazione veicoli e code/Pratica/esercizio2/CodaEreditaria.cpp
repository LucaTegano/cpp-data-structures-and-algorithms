#include "CodaEreditaria.h"

using namespace std;


// la lista va in questo verso:
// 0 -------------->   size()-1
void CodaEreditaria::aggiungi(const Studente& s) {
    for (Studente studente : *this) 
        if (studente.getMatricola() == s.getMatricola())
            return;
    
    for (auto it=this->begin(); it!=this->end(); ++it) {

        // media > 28 -> ordino per ordine di arrivo
        if (s.getMedia() >= 28.0) {
            if (it->getMedia() < 28.0) {  
                this->insert(it, s);
                return;
            } 
        }

        // 26 < media <= 28 -> ordino per matricola 
        else if (s.getMedia() >= 26.0) {
            if (it->getMedia() < 26.0 ||  
                 it->getMatricola() > s.getMatricola()) {  
                this->insert(it, s);
                return;
            }
        }

        // rimanenti (media <= 26) -> ordino per ISEE
        else {
            if (it->getIsee() > s.getIsee()) {
                this->insert(it, s);
                return;
            }
        }
        
    }

    this->push_back(s);
}


Studente CodaEreditaria::prossimo() const {
    return front();
}


void CodaEreditaria::rimuovi() {
    erase(begin());
}


unsigned int CodaEreditaria::size() const {
    // specifichiamo lo scope per evitare una chiamata ricorsiva a CodaEreditaria::size()
    return vector<Studente>::size();  
}
    
