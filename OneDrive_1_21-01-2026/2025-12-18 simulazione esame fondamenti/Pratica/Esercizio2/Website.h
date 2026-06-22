#ifndef WEBSITE_H
#define WEBSITE_H

#include "Webpage.h"
#include <queue>
#include <algorithm>

using namespace std;


class Website {
    private:    
        Webpage homepage; 

    public:
        Website() = default; 
        Website(Webpage h): homepage(h) {}

        int find_webpage(const Webpage& target) const {
            queue<Webpage> daVisitare;
            daVisitare.push(homepage);

            vector<Webpage> visitate;
            visitate.push_back(homepage);

            int level = 0;  // contatore dei livelli
            
            while (!daVisitare.empty()) {
                int levelSize = daVisitare.size();  // numero di nodi in questo livello
                
                // processa tutti i nodi del livello corrente
                for (int i = 0; i < levelSize; i++) {
                    Webpage curr_page = daVisitare.front();
                    daVisitare.pop();
                    
                    // se ho trovato target, ritorno il livello
                    if (curr_page == target)
                        return level;
                    
                    for (Webpage* w : curr_page.getLink()) {
                        if (find(visitate.begin(), visitate.end(), *w) == visitate.end()) {
                            visitate.push_back(*w);
                            daVisitare.push(*w);
                        }
                    }
                }
                
                level++;  // incrementa il livello dopo aver processato tutti i nodi del livello
            }

            return -1;
        }
};

#endif