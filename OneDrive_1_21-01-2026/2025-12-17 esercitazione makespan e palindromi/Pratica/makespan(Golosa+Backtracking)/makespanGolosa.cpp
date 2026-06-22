//
// Created by admin on 17/12/2025.
//

//IDEA EURISTICA: si ordinano i job per tempo di processamento decrescente e si assegna, ogni volta, il job più lungo alla macchina con meno lavoro

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;


void risolviConEuristica(vector<int>& jobs, vector<vector<int>>& assignment, int num_macchine, vector<int>& lavoro_macchina);
int getMacchinaPiuScarica(vector<int>& lavoro_macchina, int num_macchine);
void stampaSoluzione(vector<vector<int>>& assignment, vector<int>& lavoro_macchina, int num_macchine);

int main(){

	// vector<int> jobs{5, 4, 3, 1, 2, 1};
	// int num_macchine=2;

	vector<int> jobs{62, 14, 75, 72, 83, 4, 79, 2, 89, 19, 52, 59, 54, 58, 61};
	int num_macchine = 3;
	// int num_macchine = 2;
	// vector<int> jobs{76,32,111,2,22,60,100,37,65,65,114,68,121,71,99,127,59,47,70,43};
	// vector<int> jobs{215,31,234,72,113,153,101,235,62,225};
	// int num_macchine = 3;
	// vector<int> jobs{85,45,88,242,60,103,248,109,214,127,93,213,99,32,29,88,232,147,197,208,3,216,203,134,9,226,69,31,171,85,135,107,232,222,99,41,176,198,1,139,74,93,203,24,227,84,111,208,230,159 };
	// int num_macchine = 5;


	vector<vector<int>> assegnamenti(num_macchine); //assegnamenti[i] contiene la lista dei job processati dalla macchina i

	vector<int> lavoro_macchina(num_macchine,0);

	risolviConEuristica(jobs, assegnamenti, num_macchine, lavoro_macchina);

	stampaSoluzione(assegnamenti, lavoro_macchina, num_macchine);

	return 0;
}

void risolviConEuristica(vector<int>& jobs, vector<vector<int>>& assegnamenti, int num_macchine, vector<int>& lavoro_macchina){


	for (int i = 0; i < num_macchine; i++)
		lavoro_macchina[i] = 0;

	sort(jobs.begin(), jobs.end(), greater<int>()); // ordino i job in ordine decrescente O (nlogn)

	//assegno il job più lungo alla macchina attualmente più scarica O(n m)
	for(auto job:jobs){

		int macchina = getMacchinaPiuScarica(lavoro_macchina, num_macchine);
		lavoro_macchina[macchina] += job;
		assegnamenti[macchina].push_back(job);

	}


}

int getMacchinaPiuScarica(vector<int>& lavoro_macchina, int num_macchine){

	int macchina_piu_scarica = 0;
	int lavoro_macchina_piu_scarica = lavoro_macchina[macchina_piu_scarica];

	for(int i = 1; i < num_macchine; i++){
		if(lavoro_macchina[i] < lavoro_macchina_piu_scarica){
			lavoro_macchina_piu_scarica = lavoro_macchina[i];
			macchina_piu_scarica = i;
		}
	}

	return macchina_piu_scarica;

}

void stampaSoluzione(vector<vector<int>>& assegnamenti, vector<int>& lavoro_macchina, int num_macchine){
	int massimo = INT_MIN;
	for(int i = 0; i < num_macchine; i++){

		cout <<  endl << "Macchina " << i << " esegue i seguenti job: "<<endl;

		for(auto job: assegnamenti[i]){
			cout << job << " ";
		}

		cout << endl << "Durata totale: " << lavoro_macchina[i] << endl << endl;

		if(lavoro_macchina[i] > massimo)
			massimo = lavoro_macchina[i];


	}

	cout << endl << "Soluzione euristica: " << massimo << endl;
}