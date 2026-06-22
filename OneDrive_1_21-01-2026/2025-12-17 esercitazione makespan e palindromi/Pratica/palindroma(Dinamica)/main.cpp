#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string s;
const int SIZE = 1001;
int dp [SIZE][SIZE];

void Initialize ()
{
   for (int i = 0 ; i < SIZE ; i++)
      for (int j = 0 ; j < SIZE ; j++)
         dp[i][j]=-1;
}

int longestPalindrom (int i , int j)
{
   if (dp[i][j]!=-1)
      return dp[i][j];
   if (i>j)
      return 0;
   if (i == j)
      return 1;
   if (i<j  && s[i]==s[j])
   {
      dp[i][j] = 2+ longestPalindrom(i+1, j-1);
      return dp[i][j];
      //Se scrivo return 2 + longestPalindrom(i+1, j-1) il programma non è più dinamico perchè non salvo le sottosoluzioni
   }
   if (i<j && s[i]!=s[j])
   {
      dp[i][j]= max(longestPalindrom(i+1,j),longestPalindrom(i,j-1));
      //Se scrivo return max(longestPalindrom(i+1,j),longestPalindrom(i,j-1)) il programma non è più dinamico perchè non salvo le sottosoluzioni
      return dp[i][j];
   }
   return 0;
}

int main()
{
   int t ;
   cin >> t;
   cin.ignore();
   while(t--)
   {
      Initialize();
      getline(cin,s);
      cout<<longestPalindrom(0,s.size()-1)<<endl;
   }
}
