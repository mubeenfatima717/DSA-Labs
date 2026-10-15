#include <iostream>
using namespace std;

// read sorted registration numbers from user
void inputSortedIDs(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "enter sorted id " << i + 1 << ": ";
        cin >> arr[i];
    }
}

// verify that the array is sorted in ascending order
bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // if any element is greater than the next, it is not sorted
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

// iterative binary search function
int binarySearch(int arr[], int low, int high, int target) {
    while (low <= high) {
        // calculate mid safely without integer overflow
        int mid = low + (high - low) / 2;

        // return index if target is found at mid
        if (arr[mid] == target) {
            return mid;
        }

        // if target is greater, ignore left half
        if (arr[mid] < target) {
            low = mid + 1;
        }
        // if target is smaller, ignore right half
        else {
            high = mid - 1;
        }
    }

    // target is absent from array
    return -1;
}

// display search result
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

    // handle empty array edge case
    if (n <= 0) {
        cout << "array is empty." << endl;
        displayResult(-1);
        return 0;
    }

    int arr[100];
    inputSortedIDs(arr, n);

    // validate sorted order before proceeding
    if (!isSorted(arr, n)) {
        cout << "error: array is not sorted. binary search requires sorted input." << endl;
        return 0;
    }

    int target;
    cout << "enter target id to search: ";
    cin >> target;

    // perform binary search
    int foundIndex = binarySearch(arr, 0, n - 1, target);
    displayResult(foundIndex);

    return 0;
}