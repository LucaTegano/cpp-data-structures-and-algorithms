#include <iostream>
#include <vector>
using namespace std;

/*Dato un intero n, generare tutte le possibili stringhe s, contenenti n parentesi (, che siano ben parentesizzate.
Esempio: n = 2 -> "()()", "(())"
         n = 3 -> "((()))" "(()())" "(())()" "()(())" "()()()"
*/
struct Soluzione{
    vector<string> benFormate;
    string current;
    int n;

    Soluzione(int n_): n(n_), current(""){} 
};

void remove(Soluzione& sol){
    sol.current.pop_back();
}

string get(int i){
    if(i==0)
        return "(";
    return ")";
}

bool canAdd(string par, Soluzione sol){
    int count_aperte = 0;
    for(int i = 0; i < sol.current.size(); i++)
        if(sol.current[i] == '(')
            count_aperte ++;

    if(par == "(")
        if(count_aperte == sol.n)
            return false;
        else 
            return true;


    //se arrivo qui par == )
    if(count_aperte > sol.current.size()-count_aperte)
        return true;
    else
        return false;
    
}

void add(string par, Soluzione& sol){
    sol.current += par;
}

bool isComplete(Soluzione sol){
    return sol.current.size() == 2 * sol.n;
}
void solve(Soluzione& sol){
    
    for(int i = 0; i < 2; i++){
        if(canAdd(get(i), sol)){
            add(get(i), sol);
            if(isComplete(sol))
                sol.benFormate.push_back(sol.current);//invece di return true

            solve(sol); //invece di if solve return true
            remove(sol);
        }
    }
}
int main(){
    Soluzione sol(3);

    solve(sol);

    for(string benFormata : sol.benFormate)
        cout << benFormata << endl;

    return 0;
}