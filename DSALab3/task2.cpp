#include <iostream>
#include <string>
using namespace std;

class StringPool {
public:
    string* stringPool; 
    int currentSize;    // curr no. of strings
    int maxSize;        // max size of pool

    // constructor
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string[maxSize];
    }

    // adding string to pool
    void addString(string str) {
        if (currentSize < maxSize) {
            stringPool[currentSize] = str;
            currentSize++;
            cout << "added: " << str << endl;
        } else {
            cout << "pool is full" << endl;
        }
    }

    // remove string without freeing memory
    void removeString(int index) {
        if (index >= 0 && index < currentSize) {
            cout << "removed: " << stringPool[index] << " (without freeing memory)" << endl;
            // shifting remaining elements
            for (int i = index; i < currentSize - 1; i++) {
                stringPool[i] = stringPool[i + 1];
            }
            currentSize--;
        } else {
            cout << "invalid index" << endl;
        }
    }

    // displaying pool status
    void displayPool() {
        cout << "\npool status (" << currentSize << "/" << maxSize << "):" << endl;
        if (currentSize == 0) {
            cout << "pool is empty" << endl;
        }
        for (int i = 0; i < currentSize; i++) {
            cout << "[" << i << "] " << stringPool[i] << endl;
        }
        cout << endl;
    }
    // destructor 
    ~StringPool() {
        delete[] stringPool;
        stringPool = nullptr; 
    }
};

int main() {
    // dynamically creating string pool obj
    StringPool* pool = new StringPool();

    // add multiple strings
    pool->addString("hello");
    pool->addString("world");
    pool->addString("cplusplus");
    pool->displayPool();

    // removing string without freeing memory
    pool->removeString(1);
    pool->displayPool();

    //fiximg memory leak by deleting the pool and setting pointer to null
    delete pool;
    pool = nullptr; 
    cout << "memory cleaned up and dangling pointer avoided." << endl;
    return 0;
}