#include <iostream>
using namespace std;

int main() 
{
	unsigned input;
	cin<<input<<endl;
	unsigned somma = 0;
	unsigned counter = 1;

	while(somma < input) 
	{
		somma += counter++;
	}
	if (somma == input) 
	{
	cout<<"Il numero"<<input<<" è triangolare"<<endl;	
	}
	return 0;
}

