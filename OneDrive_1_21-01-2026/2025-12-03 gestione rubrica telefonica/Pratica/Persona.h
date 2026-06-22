#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
using namespace std;

class Persona{

    friend istream& operator>> (istream& in, Persona& v){
        cout << "Inserisci il nome -> ";
        in >> v.nome;

        cout << endl << "Inserisci il cognome -> ";
        in >> v.cognome;

        cout << endl;

        return in;

    }

    friend ostream& operator<< (ostream& out, const Persona& v){
        out << "Nome: " << v.nome << endl;
        out << "Cognome: " << v.cognome << endl;
       
        return out;
    }

    
    private:
        string nome;
        string cognome;

    public:
        
        string getNome()const {return nome;}
        string getCognome()const {return cognome;}

        bool operator==(const Persona& v)const {return v.nome == nome && v.cognome == v.cognome;} //se due VoceRubrica hanno lo stesso hash finiscono nello stesso bucket, dunque serve == per trovare quello giusto

};
#endif