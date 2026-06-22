/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Prodotto{
    private:
    unsigned int id;
    string nome;
    //la variabile va dichiarata dentro la classe, 
    //ma inizializzata fuori dalla classe 
    //(solitamente nel file .cpp o subito dopo la classe se sei in un file unico)
    static unsigned int progressivo;
    // con c++17 inline static int progressivo = 0;
    public:
    Prodotto(string nome):id(progressivo++),nome(nome){
        cout<<endl<<this;
        cout<<"progressivo dopo la creazione"<<progressivo<<endl;
        
    }
    
    bool operator<(const Prodotto& p2){
        
        return nome<p2.nome;
    }
    bool operator==(const Prodotto& p2){
        return nome==p2.nome&&id==p2.id;
    }
    friend ostream & operator<<(ostream & o, const Prodotto & p){
        o<<p.id<<p.nome<<"progressivo:"<<progressivo<<endl;
        return o;
    }
    string getNome()const{return nome;}
    
};

unsigned int Prodotto::progressivo=0;

bool mycmp(const Prodotto& p1, const Prodotto& p2){
    return p1.getNome()>p2.getNome();
}

int main()
{
    Prodotto p1("Sale");
    cout<<p1;
    Prodotto p2("Pepe");
    cout<<p1;
    cout<<p2;
    Prodotto p3("Sale");
    cout<<p1;
    cout<<p2;
    cout<<p3;
    return 0;
}