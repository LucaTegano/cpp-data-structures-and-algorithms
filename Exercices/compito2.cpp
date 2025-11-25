#include <iostream>
#include <cmath>

using namespace std;

class NumeroRazionale
{
private:
    int numeratore;
    int denominatore;

    int mcd(int a, int b)
    {
        a = abs(a);
        b = abs(b);
        while (b != 0)
        {
            int tmp = b;
            b = a % b;
            a = tmp;
        }
        return a;
    }

    void riduci()
    {
        if (denominatore < 0)
        {
            numeratore = -numeratore;
            denominatore = -denominatore;
        }

        if (numeratore == 0)
        {
            denominatore = 1;
            return;
        }

        int divisore = mcd(numeratore, denominatore);
        numeratore /= divisore;
        denominatore /= divisore;
    }

public:
    NumeroRazionale() : numeratore(0), denominatore(1) { cout << "Costuttore senza parametri" << endl; }

    NumeroRazionale(int numeratore1) : numeratore(numeratore1), denominatore(1)
    {
        cout << "Costuttore con 1 parametro" << endl;
    }

    NumeroRazionale(int numeratore, int denominatore) : numeratore(numeratore), denominatore(denominatore)
    {
        cout << "Costruttore con 2 parametri" << endl;
        if (this->denominatore == 0)
        {
            cout << "Errore: Denominatore non può essere zero." << endl;
            this->numeratore = 0;
            this->denominatore = 1;
        }
        riduci();
    }

    NumeroRazionale(const NumeroRazionale &nr) : numeratore(nr.numeratore), denominatore(nr.denominatore)
    {
        cout << "Costruttore Copia" << endl;
    }

    NumeroRazionale &operator=(const NumeroRazionale &altro)
    {
        cout << "Operatore =" << endl;
        if (this != &altro)
        {
            numeratore = altro.numeratore;
            denominatore = altro.denominatore;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const NumeroRazionale &nr)
    {
        cout << "Operatore <<" << endl;
        os << nr.numeratore << "/" << nr.denominatore;
        return os;
    }

    friend istream &operator>>(istream &is, NumeroRazionale &nr)
    {
        int num;
        int den;

        cout << "Inserisci il numeratore " << endl;
        is >> num;
        cout << "Inserisci il denominatore " << endl;
        is >> den;

        if (den == 0)
        {
            is.setstate(ios::failbit);
        }
        else
        {
            nr.numeratore = num;
            nr.denominatore = den;
            nr.riduci();
        }

        return is;
    }

    NumeroRazionale operator+(const NumeroRazionale &altro) const
    {
        cout << "Operatore +" << endl;
        int num_ris = (this->numeratore * altro.denominatore) + (altro.numeratore * this->denominatore);
        int den_ris = this->denominatore * altro.denominatore;

        return NumeroRazionale(num_ris, den_ris);
    }

    NumeroRazionale operator*(const NumeroRazionale &other) const
    {
        cout << "Operatore *" << endl;
        int num_ris = this->numeratore * other.numeratore;
        int den_ris = this->denominatore * other.denominatore;

        return NumeroRazionale(num_ris, den_ris);
    }
};

int main()
{
    cout << "--Test Costruttori--" << endl;

    NumeroRazionale r0;
    cout << "r0 (default): " << r0 << endl;

    NumeroRazionale r1(5);
    cout << "r1 (1 param 5): " << r1 << endl;

    NumeroRazionale r2(8, 12);
    cout << "r2 (2 param 8/12): " << r2 << endl;

    NumeroRazionale r_segno(5, -10);
    cout << "r_segno (5/-10): " << r_segno << endl;

    cout << "Test costruttore (10, 0):" << endl;
    NumeroRazionale r_err(10, 0);
    cout << "r_err (10/0): " << r_err << endl;

    cout << "\n--Test Copia e Assegnazione--" << endl;
    NumeroRazionale r_copia(r2);
    cout << "r_copia (di r2 2/3): " << r_copia << endl;

    r0 = r_segno;
    cout << "r0 = r_segno (-1/2): " << r0 << endl;

    cout << "\n**Test Operatori Aritmetici **" << endl;
    NumeroRazionale a(1, 2);
    NumeroRazionale b(1, 3);
    cout << "a = " << a << ", b = " << b << endl;

    NumeroRazionale somma = a + b;
    cout << "a + b = " << somma << endl;

    NumeroRazionale prodotto = a * b;
    cout << "a * b = " << prodotto << endl;

    NumeroRazionale c(2, 3);
    NumeroRazionale d(3, 4);
    cout << "c = " << c << ", d = " << d << endl;
    cout << "c * d = " << c * d << endl;

    cout << "\n**Test Operatore Input (>>)**" << endl;
    NumeroRazionale r_input;

    cin >> r_input;
    cout << "Hai inserito (ridotto): " << r_input << endl;

    return 0;
}
