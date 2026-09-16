#include <iostream>
using namespace std;

void swapByDoublePointer(int **x, int **y) {
    int temp = **x;
    **x = **y;
    **y = temp;
}

int main() {
    int a=5, b=10; 
	int *pa=&a; // pointer variables 
	int *pb=&b;
	
	int **ppa=&pa; // pointers-to-pointers.
	int **ppb=&pb;
    cout<< "before swapping: " <<"\na = "<<a<<"\nb = "<<b;
    // calling the function
    swapByDoublePointer( ppa, ppb);
    cout<< "\nafter swapping: " <<"\na = "<<a<<"\nb = "<<b;
    return 0;
}