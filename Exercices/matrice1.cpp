#include <iostream>
using namespace std;

int **min_x(const int **mat, const int righe, const int colonne)
{
  int min = mat[0][0];
  for (int i = 0; i < righe; ++i)
  {
    for (int j = 0; j < colonne; ++j)
    {
      if (mat[i][j] < min)
      {
        min = mat[i][j];
      }
    }
  }
  const int n_dim = min;
  int **n_mat = new int *[n_dim];
  for (int i = 0; i < n_dim; ++i)
  {
    n_mat[i] = new int[n_dim];
    for (int j = 0; j < n_dim; ++j)
    {
      n_mat[i][j] = mat[i][j];
    }
  }
  return n_mat;
}

int main()
{
  const int righe = 5;
  const int colonne = 7;
  int **mat = new int *[righe];
  for (int i = 0; i < righe; ++i)
  {
    mat[i] = new int[colonne];
  }
  int **min_mat = min_x(mat, righe, colonne);
  for (int i = 0; i < righe; ++i)
  {
    delete[] mat[i];
  }
  delete[] mat;

  for (int i = 0; i < righe; ++i)
  {
    delete[] min_mat[i];
  }
  delete[] min_mat;

  return 0;
}
