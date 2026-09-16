#include <iostream>
using namespace std;

void swapByAddress(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a=5, b=10; 
	int *pa=&a; //pointers 
	int *pb=&b;
	
	int **ppa=&pa; // pointers-to-pointers.
	int **ppb=&pb;
    cout<< "before swapping: " <<"\na = "<<a<<"\nb = "<<b;
    // calling the function
    swapByAddress( pa, pb);
    cout<< "\nafter swapping: " <<"\na = "<<a<<"\nb = "<<b;
    return 0;
}