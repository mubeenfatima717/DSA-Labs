#include <iostream>
using namespace std;

// display array contents
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// merge two sorted subarrays into one sorted range
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // create temporary arrays
    int L[100], R[100];

    // copy data to temporary subarrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    // merge temporary arrays back into arr
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // copy remaining elements of L if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // copy remaining elements of R if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// divide and conquer recursive merge sort
void mergeSort(int arr[], int left, int right) {
    // base case when subarray has 0 or 1 element
    if (left >= right) {
        return;
    }

    // find midpoint
    int mid = left + (right - left) / 2;

    // recursively sort left and right halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // merge the sorted halves
    merge(arr, left, mid, right);
}

int main() {
    int n;
    cout << "enter number of students: ";
    cin >> n;

    if (n <= 0) {
        cout << "empty array. nothing to sort." << endl;
        return 0;
    }

    int arr[100];
    cout << "enter " << n << " marks:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "\noriginal marks: ";
    displayArray(arr, n);

    // perform merge sort
    mergeSort(arr, 0, n - 1);

    cout << "sorted marks:   ";
    displayArray(arr, n);

    return 0;
}