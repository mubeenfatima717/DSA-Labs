#include <iostream>
#include <iomanip>
using namespace std;

// maximum board size
const int MAX = 10;
int board[MAX][MAX];

// eight possible knight moves (row and column offsets)
int dx[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
int dy[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

// check if cell is within board and unvisited
bool isValid(int row, int col, int n) {
    return (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == -1);
}

// recursive backtracking function to find knight's tour
bool solveKnightTour(int row, int col, int moveNumber, int n) {
    // base case: all n^2 squares visited successfully
    if (moveNumber > n * n) {
        return true;
    }

    // explore all eight possible candidate moves
    for (int i = 0; i < 8; i++) {
        int nextRow = row + dx[i];
        int nextCol = col + dy[i];

        if (isValid(nextRow, nextCol, n)) {
            // mark candidate move
            board[nextRow][nextCol] = moveNumber;

            // recursive call for next move
            if (solveKnightTour(nextRow, nextCol, moveNumber + 1, n)) {
                return true;
            }

            // backtrack if move leads to a dead end
            board[nextRow][nextCol] = -1;
        }
    }

    // no legal move completed the tour from this square
    return false;
}

// display the numbered chessboard
void printBoard(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(3) << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "enter board size n (e.g. 5): ";
    cin >> n;

    int startX, startY;
    cout << "enter start row (0 to " << n - 1 << "): ";
    cin >> startX;
    cout << "enter start col (0 to " << n - 1 << "): ";
    cin >> startY;

    // initialize board with -1 (unvisited)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = -1;
        }
    }

    // place knight at starting position as move 1
    board[startX][startY] = 1;

    // start recursive tour from move 2
    if (solveKnightTour(startX, startY, 2, n)) {
        cout << "\nknight's tour found successfully:\n";
        printBoard(n);
    } else {
        cout << "\nno valid knight's tour found for this search.\n";
    }

    return 0;
}