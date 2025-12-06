#include <iostream>
using namespace std;
int main()
{
int* matricola = new int[6]{262264}; //scrivi sul foglio la tua matricola
//1. La seguente istruzione è corretta? Se sì, cosa stampa?
cout << *(matricola + 3) << *(matricola + 2) << endl;//2  2
//2. La seguente istruzione è corretta? Se sì, cosa stampa?
cout << *(matricola[0]) << endl;//NO
//3. Cosa viene stampato dalla seguente porzione di codice?
int& a = matricola[4];//6
int b = matricola[5];//4
--a;//5
b += 1;//5
cout << matricola[4] << " " << matricola[5] << endl;//5 4
//4. Come andrebbe deallocata la memoria dinamica allocata inizialmente?
//A
for(int i = 0; i < 6; i++)
delete matricola[i];
//B
for(int i = 0; i < 6; i++)
delete *matricola[i];
//C
Nel main non serve deallocare la memoria dinamica.
//D
delete [] matricola;//D
}