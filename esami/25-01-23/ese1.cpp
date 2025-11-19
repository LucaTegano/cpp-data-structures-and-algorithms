// Data la seguente porzione di programma rispondere alle domande corrispondenti:

void f(int &a)
{
    if (a % 2 == 0)
        a++;
    else
        a -= 2;
}
int &g(int &a)
{
    int b = a;
    return b;
}
int main()
{
    int *matricola = new int[6]{... inserisci la tua matricola…};
    // 1. Le istruzioni seguenti sono corrette? Se si, cosa viene stampato?
    f(g(matricola[2]));
    cout << matricola[2] << endl;
    // 2. Le istruzioni seguenti sono corrette? Se si, cosa viene stampato?
    int *p = matricola + 4;
    int *q = matricola + 3;
    p = q;
    q = p;
    *p = 0;
    *q = 9;
    cout << *(matricola + 3) << “ “ << *(matricola + 4) << endl;
    // 3. La seguente istruzione è corretta? Se si, cosa viene stampato?
    cout << matricola[matricola + 2] << endl;
    // 4. Selezionare TUTTE le operazioni necessarie per deallocare la memoria allocata nel
    programma
        // a. delete[] matricola;
        // b. delete p;
        // c. for (int i=0; i < 6; i++) {delete matricola[i];}
        // d. delete matricola;
        // e. delete q;
        return 0;
}