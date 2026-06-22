/*
 * Created by Elena Mastria on 23/10/24.
 */
//

#ifndef UNTITLED_DATA_H
#define UNTITLED_DATA_H


#include <iostream>

using namespace std;

class Data {
    private:
        int giorno;
        int mese;
        int anno;


    public:
        Data(int giorno, int mese, int anno);

        Data();

        Data(const Data& oData);

        int getGiorno() const;

        void setGiorno(int giorno);

        int getMese() const;

        void setMese(int mese);

        int getAnno() const;

        void setAnno(int anno);

        Data& operator=(const Data& oData);

        bool operator<(const Data&) const;

        friend ostream& operator<<(ostream& out, const Data& s);

        friend istream& operator>>(istream& out, Data& s);


};


#endif //UNTITLED_DATA_H
