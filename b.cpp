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
  // This is the main function where the program execution begins.
  // It prompts the user to enter an integer, calculates its factorial
  // using the 'fact' function, and then prints the result to the console.
  int val;
  cin >> val;
  cout << fact(val) << endl;
  return 0;
};
