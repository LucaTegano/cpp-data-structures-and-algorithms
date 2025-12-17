#include <iostream>

using namespace std;

// Dimensione della griglia (9x9)
#define N 9

/*
 * Funzione di utilità per stampare la griglia
 */
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

/*
 * Controlla se è sicuro assegnare il numero 'num' alla cella grid[row][col].
 * Verifica:
 * 1. La riga
 * 2. La colonna
 * 3. Il box 3x3
 */
bool isSafe(int grid[N][N], int row, int col, int num) {
    
    // 1. Controlla la riga
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num)
            return false;

    // 2. Controlla la colonna
    for (int x = 0; x < N; x++)
        if (grid[x][col] == num)
            return false;

    // 3. Controlla il box 3x3
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

/*
 * Funzione principale che risolve il Sudoku usando il Backtracking.
 * Ritorna true se esiste una soluzione, false altrimenti.
 */
bool solveSudoku(int grid[N][N], int row, int col) {
    
    // CASO BASE: Se siamo arrivati alla fine della griglia (riga N-1 e colonna N)
    // vuol dire che abbiamo riempito tutto correttamente.
    if (row == N - 1 && col == N)
        return true;

    // Se la colonna arriva alla fine (N), passa alla riga successiva e resetta colonna a 0
    if (col == N) {
        row++;
        col = 0;
    }

    // Se la cella corrente è già piena (diversa da 0), passiamo alla prossima colonna
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    // Proviamo i numeri da 1 a 9 nella cella corrente
    for (int num = 1; num <= 9; num++) {
        
        // Se è sicuro piazzare il numero...
        if (isSafe(grid, row, col, num)) {
            
            // ...lo piazziamo (DO step)
            grid[row][col] = num;

            // Ricorsione: proviamo a risolvere il resto della griglia
            if (solveSudoku(grid, row, col + 1))
                return true;
        }

        // BACKRACKING (UNDO step):
        // Se assegnare 'num' non porta a una soluzione, rimuoviamolo (rimettiamo 0)
        // e proviamo con il prossimo numero del ciclo for.
        grid[row][col] = 0;
    }
    
    // Se nessun numero da 1 a 9 va bene, torniamo false (triggera il backtracking allo step precedente)
    return false;
}

int main() {
    // 0 rappresenta le celle vuote
    int grid[N][N] = { 
        { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
        { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
        { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
        { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
        { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
        { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
        { 0, 0, 5, 2, 0, 6, 3, 0, 0 } 
    };

    if (solveSudoku(grid, 0, 0))
        printGrid(grid);
    else
        cout << "Nessuna soluzione esiste" << endl;

    return 0;
}
