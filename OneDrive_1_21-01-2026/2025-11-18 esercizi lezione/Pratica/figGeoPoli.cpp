#include<iostream>
#include<vector>

using namespace std;

class FigGeo{
  public:
     virtual void stampa(){cout<<"Figura Geometrica"<<endl;}
     virtual double area()=0;
     virtual ~FigGeo(){ cout<<"distruttore di Figura Geometrica"<<endl;} 
     //DOMANDA che succede se ometto virtual dal distruttore? Perche'?
     //DOMANDA avrei invece potuto scrivere virtual ~FigGeo()=0; (come metodo virtuale puro) 
};

class Quadrato:public FigGeo
{
   private:
     double lato;
   public:
     Quadrato(double l1=0):lato(l1){}
     void setLato(double l1){lato=l1;}
     double getLato(){return lato;}
     void stampa(){ cout<<"quadrato di lato "<<lato<<endl;}
     //DOMANDA avrei potuto omettere la ridefinizione del metodo stampa? e quella del metodo area? cosa succederebbe?
     double area(){return lato*lato;}
     ~Quadrato(){ cout<<"distruttore di Quadrato"<<endl;}

};

class Cerchio:public FigGeo
{
   private:
     double raggio;
   public:
     Cerchio(double r1=0):raggio(r1){}
     void setRaggio(double r1){raggio=r1;}
     double getRaggio(){return raggio;}
     void stampa(){cout<<"cerchio di raggio "<<raggio<<endl;}
     double area(){return 3.14*raggio*raggio;}
     ~Cerchio(){ cout<<"distruttore di Cerchio"<<endl;}

};

class Rettangolo:public FigGeo
{
   private:
     double base,altezza;
   public:
     Rettangolo(double b=0,double h=0):base(b),altezza(h){}
     void setBase(double b){base=b;}
     double getBase(){return base;}
     void setAltezza(double h){altezza=h;}
     double getAltezza(){return altezza;}
     void stampa(){ cout<<"rettangolo di base "<<base<<" e altezza "<<altezza<<endl;}
     double area(){return base*altezza;}
     ~Rettangolo(){ cout<<"distruttore di Rettangolo"<<endl;}

};

void f(FigGeo &f)
{
   f.stampa();
}

int main()
{

   vector<FigGeo*> V;
   V.push_back(new Quadrato(3));   
   V.push_back(new Cerchio(2));
   V.push_back(new Rettangolo(3,5));   
   V.push_back(new Cerchio(4));
   V.push_back(new Quadrato(6));   
   V.push_back(new Rettangolo(7,6));
   for (vector<FigGeo*>::iterator it=V.begin(); it!= V.end(); it++)
        cout<<(*it)->area()<<" ";
   cout<<endl;
   for (vector<FigGeo*>::iterator it=V.begin(); it!= V.end(); it++)
        delete *it; 

   Quadrato q(1);
   f(q); //COSA FA questa istruzione? cosa stampa? Perchè?
}
