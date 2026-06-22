#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Prodotto{
    private:
    int id;
    string nome;
    public:
    
    
    Prodotto(int id, string nome):id(id),nome(nome){}
    
   /* bool operator<(const Prodotto& p2){
        return nome<p2.nome;
    }*/
    /*bool operator==(const Prodotto& p2){
        return nome==p2.nome&&id==p2.id;
    }*/
    friend ostream & operator<<(ostream & o, const Prodotto & p){
        o<<p.id<<p.nome;
        return o;
    }
    string getNome()const{return nome;}
    
};

bool mycmp(const Prodotto& p1, const Prodotto& p2){
    return p1.getNome()>p2.getNome();
    
}
int main()
{
    Prodotto p1(10,"Sale");
    Prodotto p2(1,"Pepe");
    Prodotto p3(1,"Sale");
    vector<Prodotto> v={p1,p2};
    for(Prodotto p:v){
        cout <<p  << endl;
        
    }
    sort(v.begin(),v.end(),mycmp);
    for(Prodotto p:v){
        cout <<p  << endl;
        
    }
    vector<Prodotto>::iterator it=find(v.begin(),v.end(),p3);
    if(it!=v.end())
        cout<<*(it);
    else
        cout<<"not found";
    return 0;
}