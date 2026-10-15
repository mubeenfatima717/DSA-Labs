#include <iostream>
using namespace std;

// read student ids into array
void inputIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "enter id for student " << i + 1 << ": ";
        cin >> arr[i];
    }
}
// search for target id sequentially
int linearSearch(int arr[], int n, int target) {
    // check for empty array
    if (n <= 0) {
        return -1;
    }
    // traverse from index 0 to n - 1
    for (int i = 0; i < n; i++) {
        // return immediately when first match is found
        if (arr[i] == target) {
            return i;
        }
    }
    // return -1 if loop finishes without finding target
    return -1;
}
// display result based on returned index
void displayResult(int index) {
    if (index != -1) {
        cout << "result: id found at index " << index << endl;
    } else {
        cout << "result: id is not registered (not found)." << endl;
    }
}
int main() {
    int n;
    cout << "enter number of students: ";
    cin >> n;

    int arr[100]; // static array for simplicity
    // only take input if array is not empty
    if (n > 0) {
        inputIDs(arr, n);
    }
    int target;
    cout << "enter target id to search: ";
    cin >> target;
    // perform search and display result
    int foundIndex = linearSearch(arr, n, target);
    displayResult(foundIndex);
    return 0;
}