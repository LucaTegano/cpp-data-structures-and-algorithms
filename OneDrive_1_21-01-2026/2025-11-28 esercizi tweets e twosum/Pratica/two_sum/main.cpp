#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
vector<int> twoSum(vector<int>& nums, int target);


int main(){

	vector<int> nums{2, 3, 5, 4, 5, 4, 22, 21};
	int target = 43;
	
	vector<int> soluzione = twoSum(nums, target);
	for(int i = 0; i < soluzione.size(); i++){
		cout << "Indice: " << soluzione[i] << " - Valore: " << nums[soluzione[i]] << endl;
	}

	return 0;
}

vector<int> twoSum(vector<int>& nums, int target) {
    // la chiave è il valore nell'array mentre il valore è il suo indice 
    //(in questo caso specifico invertiamo il concetto di accesso rispetto al vettore, uso il valore per accedere al suo indice)
    unordered_map<int, int> mappa;
    vector<int> solution;

    for(int i = 0; i < nums.size(); i++){
    	

    	//se (target - nums[i]) è presente come chiave nella mappa allora ho trovato una soluzione
	//avrei potuto fare if (find != end) solution.push_back(mappa[target-nums[i]])
		auto it = mappa.find(target - nums[i]);
    	if(it != mappa.end())
    	{
    		cout<<"Soluzione trovata"<<endl;
    		solution.push_back(it -> second);
    		solution.push_back(i);
    		return solution;
    	}
    	//altrimenti inserisco chiave nums[i] e valore  i
    	else
    		mappa.insert({nums[i], i});
    	
    }

    return solution;

}
