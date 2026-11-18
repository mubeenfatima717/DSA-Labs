#include <iostream>
#include <iomanip>
using namespace std;
/*
ANSWERS TO TASK 1 QUESTIONS:
1. What is the worst-case number of swaps for one insertion into a 
   heap of n elements?
   Answer:
   The worst-case number of swaps is equal to the height of the 
   complete binary tree, which is floor(log2(n)). This happens when 
   the newly inserted element is greater than all its ancestors and 
   must sift up all the way from the leaf level to the root.

2. What is the time complexity of building the heap by n insertions, 
   and of heap sort?
   Answer:
   - Building the heap via n insertions takes O(n log n) time in the 
     worst case, because each insertion at step k takes O(log k) time.
   - Heap sort takes O(n log n) time in all cases (best, average, worst) 
     because extracting the root and sifting down takes O(log k) for 
     each of the n elements.

*/

// class implementing an array-based max heap without stl
class MaxHeap {
private:
    int* arr;
    int size;
    int capacity;

    // helper function to swap two integers
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // restores max heap property downwards
    // time complexity: o(log n)
    void siftDown(int i, int heapSize) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heapSize && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < heapSize && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            siftDown(largest, heapSize);
        }
    }

public:
    // constructor allocating dynamic array
    // time complexity: o(1)
    MaxHeap(int cap = 50) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
    }

    // destructor freeing dynamic memory
    // time complexity: o(1)
    ~MaxHeap() {
        delete[] arr;
    }

    // inserts value at the end and sifts up while counting swaps
    // time complexity: o(log n)
    int insert(int value) {
        if (size >= capacity) {
            cout << "heap is full!" << endl;
            return 0;
        }

        // place element at the end of the heap
        int current = size;
        arr[current] = value;
        size++;

        int swaps = 0;

        // sift up: compare current element with its parent at (i - 1) / 2
        while (current > 0) {
            int parent = (current - 1) / 2;
            if (arr[current] > arr[parent]) {
                swap(arr[current], arr[parent]);
                swaps++;
                current = parent;
            } else {
                break;
            }
        }

        return swaps;
    }

    // prints the elements currently in the heap
    // time complexity: o(n)
    void printHeap() const {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // sorts heap contents in ascending order using sift-down
    // time complexity: o(n log n)
    void heapSort() {
        // extract elements one by one from the heap
        for (int i = size - 1; i > 0; i--) {
            // move current root (maximum) to the end
            swap(arr[0], arr[i]);

            // call sift-down on the reduced heap
            siftDown(0, i);
        }
    }

    // displays sorted elements
    // time complexity: o(n)
    void printSorted() const {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};



int main() {
    int inputValues[] = { 25, 40, 15, 60, 35, 10, 70, 50 };
    int n = sizeof(inputValues) / sizeof(inputValues[0]);

    MaxHeap heap(n + 10);

    cout << left << setw(10) << "Insert" 
         << setw(10) << "Swaps" 
         << "Heap after insertion" << endl;
    cout << "----------------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        int val = inputValues[i];
        int swaps = heap.insert(val);

        cout << left << setw(10) << val 
             << setw(10) << swaps;
        heap.printHeap();
    }

    cout << "\nFinal Max Heap: ";
    heap.printHeap();

    // sort in ascending order using heap sort
    heap.heapSort();

    cout << "Sorted output:  ";
    heap.printSorted();

    return 0;
}