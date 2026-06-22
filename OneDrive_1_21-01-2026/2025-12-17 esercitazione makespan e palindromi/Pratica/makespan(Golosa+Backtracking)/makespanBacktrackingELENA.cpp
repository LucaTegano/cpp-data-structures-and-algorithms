/*
 * Created by Elena Mastria on 16/12/25.
 */
//

#include <limits.h>
#include <vector>
#include <iostream>

using namespace std;

struct Soluzione {
    const vector<int>& jobs;
    int numMacchine;
    vector<int> loadMacchine;
    unsigned solution = INT_MAX;

    Soluzione(const vector<int>& jobs, int numMacchine) : jobs(jobs), numMacchine(numMacchine) {
        loadMacchine.resize(numMacchine, 0);
    }

    unsigned getCurrentMakespan() const {
        unsigned makespan = 0;
        for (int l: loadMacchine) {
            if (l > makespan) {
                makespan = l;
            }
        }
        return makespan;
    }
};


bool canAdd(unsigned job_idx, int macchina, const Soluzione& soluzione) {
    unsigned newMakespan = soluzione.loadMacchine[macchina] + soluzione.jobs[job_idx];
    if (newMakespan >= soluzione.solution) {
        cout << "non posso aggiungere il job " << job_idx <<" alla macchina "<<macchina  <<endl;
        return false;
    }
    return true;
}

void add(unsigned job_idx, int macchina, Soluzione& soluzione) {
    cout << "ASSEGNO il job: " << job_idx << " alla macchina: " << macchina << endl;
    soluzione.loadMacchine[macchina] += soluzione.jobs[job_idx];
}

void remove(unsigned job_idx, int macchina, Soluzione& soluzione) {
    cout << "RIMUOVO il job: " << job_idx << " dalla macchina: " << macchina << endl;
    soluzione.loadMacchine[macchina] -= soluzione.jobs[job_idx];
}


bool isComplete(Soluzione& soluzione, unsigned job_idx) {
    unsigned currentMakespan = soluzione.getCurrentMakespan();
    if (job_idx >= soluzione.jobs.size()) {
        if (currentMakespan < soluzione.solution) {
            soluzione.solution = currentMakespan;
        }
        return true;
    }

    return currentMakespan >= soluzione.solution;
}

void solve(Soluzione& soluzione, unsigned jobIdx) {
    //provo ad assegnare il job a tutte le macchine
    cout << "*********************\n" <<
            "processo il job: " << jobIdx << endl;

    if (isComplete(soluzione, jobIdx)) {

        return;
    }

    int macchina = 0;
    while (macchina < soluzione.numMacchine) {
        if (canAdd(jobIdx, macchina, soluzione)) {
            add(jobIdx, macchina, soluzione);
            solve(soluzione, jobIdx + 1);
            remove(jobIdx, macchina, soluzione);
            //provo ad assegnare ad una nuova macchina per vedere se trovo qualcosa di meglio
            cout << "backtracking, passo alla macchina successiva: " << macchina << endl;
        }
        macchina++;
    }
}

int main() {
    // vector<int> jobs{5, 4, 3, 1, 2, 1};
    // int macchine = 2;

    // vector<int> jobs{62, 14, 75, 72, 83, 4, 79, 2, 89, 19, 52, 59, 54, 58, 61};
    // int macchine = 3;
    // int macchine = 2;
    // vector<int> jobs{76,32,111,2,22,60,100,37,65,65,114,68,121,71,99,127,59,47,70,43};
    // vector<int> jobs{215,31,234,72,113,153,101,235,62,225};
    // int macchine = 3;
    vector<int> jobs{85,45,88,242,60,103,248,109,214,127,93,213,99,32,29,88,232,147,197,208,3,216,203,134,9,226,69,31,171,85,135,107,232,222,99,41,176,198,1,139,74,93,203,24,227,84,111,208,230,159 };
    int macchine = 5;
    Soluzione soluzione(jobs, macchine);
    solve(soluzione, 0);
    cout << soluzione.solution << endl;
    return 0;
}
