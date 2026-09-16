#include <iostream>
using namespace std;

int main() {
    int n = 3;
    // dynamic array
    int* values = new int[n]; 
    //corrected loop condition (i < n) 
    cout<< "Enter " << n << " values: ";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }
    for (int i = 0; i < n; i++) {
        cout << values[i]<< " ";
    }
    // using delete[] for arrays
    delete[] values; 
    // reset the pointer to prevent a dangling pointer
    values = nullptr; 
    return 0;
}