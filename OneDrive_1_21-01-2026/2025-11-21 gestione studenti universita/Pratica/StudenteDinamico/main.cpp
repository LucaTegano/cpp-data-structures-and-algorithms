#include <iostream>
#include "StudenteDinamico/StudenteDinamico.h"

int main() {
    StudenteDinamico * studenti=new StudenteDinamico[4];

    for (int i = 0; i < 4; ++i) {
        cin>>studenti[i];
    }
    int studenteBrillante=0;
    float cmedia=studenti[studenteBrillante].getMedia();
    for (int i = 1; i < 4; ++i) {
        float cmedia2=studenti[i].getMedia();
        if(cmedia2>cmedia){
            cmedia=cmedia2;
            studenteBrillante=i;
        }
    }
    cout<<"studente billante"<<endl;
    cout<<studenti[studenteBrillante];
    delete [] studenti;
    return 0;
}
