#include <iostream>
using namespace std;

int main()
{
	double cel;
	cout << "Inserire la temperatura in gradi Celsius"<<endl;
	cin>>cel;
	double far = (cel * 9 / 5) + 32;
	cout << "La temperatura in faranhait è " << far<<endl;
	return 0;
}
