void f(int& a) {if (a%2==0) a++; else a-=2;}

int &g(int& a) {int b=a;return b; }

int main() {
  int* matricola = new int[6]{262264};
// 1. Le istruzioni seguenti sono corrette? se si cosa viene stampato?? 
f(g(matricola[2]);//ERRORE
cout << matricola[2]<< endl; //2
}
// 2 . Le istruzioni seguenti sono corrette? se si cosa viene stampato ?
//nuova matricola 262264
int* p = matricola +4;//6
int* q = matricola +3;//2
p= q;//p punta a 2 m[3]
q=p;// q punta a 2 m[3]
*p = 0;//262064
*q=9;//262964
cout<<*(matricola+3) << " "<< *(matricola+4)<<endl;//9,6


//3. La seguente istruzione è correta? se si cosa viene stampato?
cout << matricola [matricola+2]<<endl;ERRORE

//4.Selezionare TUTTE le operazioni necessarie per deallocare la memoria allocata nel programma

//a.delete[] matricola;//SI
//b.delete p;//NO
//c for//NO
//d. delete matricola;//NO
//e. delete q; //NO


