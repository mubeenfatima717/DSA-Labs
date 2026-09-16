#include<iostream>
using namespace std;

int main(){
    int a, *pa;
    a = 4;
    pa = &a;
    pa = pa * 2;
    cout<<"pa = pa * 2 --> pa = "<<pa;

    return 0;
}