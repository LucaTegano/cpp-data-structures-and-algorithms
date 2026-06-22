#include <iostream>

#include "DocumentoRiservato.h"
#include "Libro.h"
#include "Rivista.h"
using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    Libro libro1(1, "Il Signore degli Anelli", "J.R.R. Tolkien", 1200);
    Rivista rivista1(2, "Nature", "AA.VV.", 42);
    DocumentoRiservato doc1(3, "Progetto Segreto", "John Doe", "1234");

    cout << "--- Libro ---" << endl;
    libro1.mostraDettagli();
    cout << endl;

    cout << "--- Rivista ---" << endl;
    rivista1.mostraDettagli();
    cout << endl;

    cout << "--- Modifica titolo e autore della rivista ---" << endl;
    rivista1.setTitolo("Science");
    rivista1.setAutore("Redazione");
    rivista1.setNumeroEdizione(43);
    rivista1.mostraDettagli();
    cout << endl;

    cout << "--- Documento Riservato con PIN corretto ---" << endl;
    doc1.mostraDettagli("1234");
    cout << "--- Modifica Documento Riservato ---" << endl;
    doc1.setTitolo("1234", "Progetto SuperSegreto");
    doc1.setAutore("1234", "Jane Doe");
    doc1.setId("1234", 4);
    doc1.mostraDettagli("1234");
    cout << endl;

    cout << "--- Documento Riservato con PIN errato ---" << endl;
    doc1.mostraDettagli("0000");
    doc1.setTitolo("0000", "Fail Test");
    doc1.setAutore("0000", "Nobody");
    doc1.setId("0000", 5);
    cout << endl;

    return 0;
}