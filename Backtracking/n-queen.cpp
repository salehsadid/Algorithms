#include <iostream>
#include <vector>
using namespace std;

bool safe(vector<int>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col) {
            return false;
        }
    }
    
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i] == j) {
            return false;
        }
    }
    
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i] == j) {
            return false;
        }
    }
    
    return true;
}

void printBoard(vector<int>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool solveNQueens(vector<int>& board, int row, int n) {
    if (row == n) {
        return true;
    }
    for (int col = 0; col < n; col++) {
        if (safe(board, row, col, n)) {
            board[row] = col;
            
            if (solveNQueens(board, row + 1, n)) {
                return true;
            }
            
            board[row] = -1;
        }
    }
    
    return false;
}

int main() {
    
    int n;
    cout << "Enter the value of N: ";
    cin >> n;
    
    vector<int> board(n, -1);
    
    if (solveNQueens(board, 0, n)) {
        cout << "\nSolution found:\n\n";
        printBoard(board, n);
    } else {
        cout << "No solution exists for N = " << n << endl;
    }
    
    return 0;
}
