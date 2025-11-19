#include <string>
#include <iostream>

using namespace std;

int main()
{
    string s1 = "Ciao";
    string s2("Ok");

    string s3 = s1 + s2;
    s1 += s2;

    // s1.append('a'); // NO non posso appendere un solo un carattere
    s1.push_back('a'); // Fixed: single character instead of multi-character constant

    // Acesso ai caratteri
    cout << "Primo carattere " << s3.front() << endl;
    cout << "Primo carattere " << s3.back() << endl;

    cout << "Terzo carattere " << s3[2] << endl;

    // Iterare
    for (int i = 0; i < s3.size(); ++i)
        cout << "Carattere di indice " << i << ":" << s3[i] << endl;

    // con Iteratori
    for (auto it = s3.begin(); it != s3.end(); ++it)
        cout << "Carattere: " << *it << endl;

    // Modifica di caratteri
    s3[2] = 's';

    // Sottostringhe
    string sub = s3.substr(3, 5); // (inizio,vai avanti di x)

    // Ricerca
    size_t pos = s3.find(sub); // Mi ritorna l'indice di partenza -> 3

    // Sostituzione
    s3.replace(5, 3, "ia"); // (inizio,vai avanti di x, "nuova stringa")

    // Confronti
    string a = "ciao";
    string b = "ciao";
    string c = "buongiorno";

    cout << "Uguali ?" << ((a == b) ? "True" : "False") << endl;
    cout << "Diversi" << (a != c) << endl;
}
