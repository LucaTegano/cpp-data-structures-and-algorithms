#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <string>
#include <vector>

using namespace std;


class Webpage {
    private:
        const string titolo; 
        const string testo;
        vector<Webpage*> link; 

    public:
        Webpage(): link({}) {}
        
        Webpage(const string& ti, const string& te, const vector<Webpage*>& l): titolo(ti), testo(te), link(l) {}

        string getTitolo() const {return titolo;}
        string getTesto() const {return testo;}
        const vector<Webpage*>& getLink() const {return link;}

        void aggiungiLink(Webpage* w) {link.push_back(w);}

        bool operator==(const Webpage& other) {
            return titolo==other.titolo;  
        }
};

#endif

