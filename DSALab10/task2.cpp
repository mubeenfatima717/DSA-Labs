#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// helper function to swap two integers
void swapInt(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// max heap implementation using dynamic array
class MaxHeap {
private:
    int* arr;
    int size;
    int capacity;
    
    // sifts down the element at index i to restore max heap property
    // time complexity: o(log n)
    void siftDown(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < size && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swapInt(arr[i], arr[largest]);
            siftDown(largest);
        }
    }

    // sifts up the element at index i to restore max heap property
    // time complexity: o(log n)
    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (arr[i] > arr[parent]) {
                swapInt(arr[i], arr[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

public:
    // constructor allocating memory
    // time complexity: o(1)
    MaxHeap(int cap = 100) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
    }

    // destructor freeing memory
    // time complexity: o(1)
    ~MaxHeap() {
        delete[] arr;
    }

    // inserts element into max heap
    // time complexity: o(log n)
    void push(int val) {
        if (size >= capacity) return;
        arr[size] = val;
        siftUp(size);
        size++;
    }

    // removes and returns the maximum element (root)
    // time complexity: o(log n)
    int pop() {
        if (size <= 0) return -1;
        int maxVal = arr[0];
        arr[0] = arr[size - 1];
        size--;
        siftDown(0);
        return maxVal;
    }

    // returns maximum element without removing
    // time complexity: o(1)
    int top() const {
        return (size > 0) ? arr[0] : -1;
    }

    // returns current number of elements
    // time complexity: o(1)
    int getSize() const {
        return size;
    }

    // checks if heap is empty
    // time complexity: o(1)
    bool isEmpty() const {
        return size == 0;
    }
};

// min heap implementation using dynamic array
class MinHeap {
private:
    int* arr;
    int size;
    int capacity;

    // sifts down the element at index i to restore min heap property
    // time complexity: o(log n)
    void siftDown(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && arr[left] < arr[smallest]) {
            smallest = left;
        }
        if (right < size && arr[right] < arr[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            swapInt(arr[i], arr[smallest]);
            siftDown(smallest);
        }
    }

    // sifts up the element at index i to restore min heap property
    // time complexity: o(log n)
    void siftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (arr[i] < arr[parent]) {
                swapInt(arr[i], arr[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

public:
    // constructor allocating memory
    // time complexity: o(1)
    MinHeap(int cap = 100) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
    }

    // destructor freeing memory
    // time complexity: o(1)
    ~MinHeap() {
        delete[] arr;
    }

    // inserts element into min heap
    // time complexity: o(log n)
    void push(int val) {
        if (size >= capacity) return;
        arr[size] = val;
        siftUp(size);
        size++;
    }

    // removes and returns the minimum element (root)
    // time complexity: o(log n)
    int pop() {
        if (size <= 0) return -1;
        int minVal = arr[0];
        arr[0] = arr[size - 1];
        size--;
        siftDown(0);
        return minVal;
    }

    // returns minimum element without removing
    // time complexity: o(1)
    int top() const {
        return (size > 0) ? arr[0] : -1;
    }

    // returns current number of elements
    // time complexity: o(1)
    int getSize() const {
        return size;
    }

    // checks if heap is empty
    // time complexity: o(1)
    bool isEmpty() const {
        return size == 0;
    }
};

// hospital wait-time monitor managing running median with two heaps
class WaitTimeMonitor {
private:
    MaxHeap maxHeap; // stores smaller half of waits
    MinHeap minHeap; // stores larger half of waits
    const float threshold = 35.0f;

public:
    // adds a new wait time and rebalances heaps
    // time complexity: o(log n)
    void addWait(int x) {
        // insert into appropriate heap
        if (maxHeap.isEmpty() || x <= maxHeap.top()) {
            maxHeap.push(x);
        } else {
            minHeap.push(x);
        }

        // rebalance heaps so size(maxHeap) >= size(minHeap)
        // and size(maxHeap) - size(minHeap) <= 1
        if (maxHeap.getSize() > minHeap.getSize() + 1) {
            minHeap.push(maxHeap.pop());
        } else if (minHeap.getSize() > maxHeap.getSize()) {
            maxHeap.push(minHeap.pop());
        }
    }

    // returns current running median
    // time complexity: o(1)
    double getMedian() const {
        if (maxHeap.getSize() > minHeap.getSize()) {
            return (double)maxHeap.top();
        } else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }

    // returns current root of max heap as string
    string getMaxRoot() const {
        return to_string(maxHeap.top());
    }

    // returns current root of min heap as string (or "none" if empty)
    string getMinRoot() const {
        if (minHeap.isEmpty()) return "none";
        return to_string(minHeap.top());
    }

    // returns alert status based on 35-minute threshold
    string getStatus() const {
        return (getMedian() > threshold) ? "ALERT" : "Normal";
    }
};

/*
====================================================================
ANSWERS TO TASK 2 QUESTIONS:

7. Why is the median a better alert measure here than the average? 
   Use arrival 6 in your answer.
   Answer:
   The median is resistant to extreme outliers. At arrival 6, a patient 
   arrives with an extreme wait time of 90 minutes. 
   - The median only shifts slightly from 30 to 37.5, which accurately 
     reflects the typical waiting experience of the patient population.
   - In contrast, the average would jump to (45+20+60+15+30+90)/6 = 43.33, 
     heavily distorted by that single patient. The median prevents isolated, 
     unusual cases from causing false alarms while still catching general 
     delays.

8. What goes wrong if the two heap sizes differ by two or more?
   Answer:
   If the heap sizes differ by two or more, the roots of the heaps no 
   longer point to the exact 50th percentile (the middle elements) of 
   the sorted dataset. Rebalancing guarantees that the middle elements 
   are always located at the roots. Without rebalancing, getMedian() 
   retrieves elements shifted away from the true median, returning 
   incorrect statistics.

9. How many total operations does repeated sorting need compared with 
   your heap method for n patients?
   Answer:
   - Repeated sorting: After each of the n arrivals, sorting the array 
     takes O(k log k) time. Over n arrivals, this requires a total of 
     sum_{k=1}^n O(k log k) = O(n^2 log n) operations.
   - Two-heap method: Each arrival only performs heap insertions and 
     at most one rebalance swap, costing O(log k). Over n arrivals, 
     this takes sum_{k=1}^n O(log k) = O(n log n) total operations, 
     which is exponentially faster and suitable for real-time systems.
====================================================================
*/

int main() {
    int arrivals[] = { 45, 20, 60, 15, 30, 90, 10, 55 };
    int totalArrivals = sizeof(arrivals) / sizeof(arrivals[0]);

    WaitTimeMonitor monitor;

    // print table header
    cout << left 
         << setw(10) << "Arrival" 
         << setw(10) << "Wait" 
         << setw(16) << "Max heap root" 
         << setw(16) << "Min heap root" 
         << setw(10) << "Median" 
         << "Status" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    for (int i = 0; i < totalArrivals; i++) {
        int wait = arrivals[i];
        monitor.addWait(wait);

        cout << left 
             << setw(10) << (i + 1)
             << setw(10) << wait
             << setw(16) << monitor.getMaxRoot()
             << setw(16) << monitor.getMinRoot()
             << setw(10) << monitor.getMedian()
             << monitor.getStatus() << endl;
    }

    return 0;
}