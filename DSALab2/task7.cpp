#include <iostream>
using namespace std;

int main() {
    int n = 0; // no of initial marks

    //1 reading and validateing n 
    cout << "enter number of marks (1 to 10): ";
    cin >> n;
    while (n < 1 || n > 10) {
        cout << "invalid enter a value between 1 and 10: ";
        cin >> n;
    }
    // allocating initial memory block of size n
    int* marks = new int[n];
    // reading initial marks using pointer notation
    cout << "enter " << n << " marks:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> *(marks + i);
    }
    // allocating second block of size n + 1
    int* newMarks = new int[n + 1];
    // copy original n values into new block using pointer
    for (int i = 0; i < n; i++) {
        *(newMarks + i) = *(marks + i);
    }
    // reading the new mark into the final position
    cout << "enter one additional mark: ";
    cin >> *(newMarks + n);

    // 2 releaseing old block
    delete[] marks;
    // redirecting original pointer to new block and updateing size
    marks = newMarks;
    n = n + 1;
    // displaying all values
    cout << "\nupdated marks list:" << endl;
    for (int i = 0; i < n; i++) {
        cout << *(marks + i) << " ";
    }
    cout << endl;

    // 3 releaseing final block exactly once
    delete[] marks;
    marks = nullptr;

    return 0;
}
