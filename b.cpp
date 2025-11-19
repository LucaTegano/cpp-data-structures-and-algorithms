#include <iostream>
using namespace std;

int fact(int val)
{
  if (val <= 1)
    return 1;
  else
    return fact(val - 1) * val;
};

int main()
{
  int val;
  cin >> val;
  cout << fact(val) << endl;
  return 0;
};
