#include <iostream>
#include <vector>

using namespace std;


int divCoins(const vector<int>& monete) {
    int tot=0;
    for (int i : monete)
        tot += i;
    
    int target = tot/2;

    bool sommeParziali[target+1] = {false};
    sommeParziali[0] = true;

    for (int m : monete) 
        for (int i=target-m; i>=0; --i)
            if (sommeParziali[i])
                sommeParziali[i+m]= true;

    for (int i=target; i >=0; --i)
        if (sommeParziali[i])
            return abs(i - (tot-i));
    
    return -1;
}


int main() {
    vector<int> monete;
    cout << "Inserisci le monete separate da spazio: ";
    int input; cin >> input;

    while (input != -1) {
        monete.push_back(input);
        cin >> input;
    }

    int diff = divCoins(monete);
    cout << "Diff ottima: " << diff << endl;

    return 0;
}