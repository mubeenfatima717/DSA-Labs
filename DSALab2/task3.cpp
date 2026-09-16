#include<iostream>
using namespace std;

int main(){
    //give list and pointer
    int list[5]={3,6,9,12,15}; 
    int *pArr= list; 

    //loop through the list through pointer
    for(int i=0; i<5; i++){
        cout<<*(pArr+i)<<" ";
    }

    return 0;
}