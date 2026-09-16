#include <iostream>
using namespace std;

int main() {
    int rows = 0; // no of students
    int cols = 0; // no of subjects
    // 1 read and validate rows and cols
    cout << "enter number of students (rows): ";
    cin >> rows;
    while (rows <= 0) {
        cout << "invalid enter rows > 0: ";
        cin >> rows;
    }
    cout << "enter number of subjects (cols): ";
    cin >> cols;
    while (cols <= 0) {
        cout << "invalid enter cols > 0: ";
        cin >> cols;
    }

    // 2 dynamic memory allocation
    // allocating array of row pointers
    int** marks = new int*[rows];
    // allocating cols integers for each row
    for (int r = 0; r < rows; r++) {
        marks[r] = new int[cols];
    }

    // 3 reading marks using pointer notation *(*(marks + r) + c)
    cout << "\nenter marks (0 to 100) row by row:" << endl;
    for (int r = 0; r < rows; r++) {
        cout << "enter marks for student " << (r + 1) << " (" << cols << " subjects): ";
        for (int c = 0; c < cols; c++) {
            cin >> *(*(marks + r) + c); // pointer notation required by task
        }
    }

    // 4 displaying the matrix
    cout << "\nmarks matrix:" << endl;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << *(*(marks + r) + c) << "\t";
        }
        cout << endl;
    }

    // 5 calculating totals and finding highest total
    // determine first student's total first
    int bestTotal = 0;
    for (int c = 0; c < cols; c++) {
        bestTotal += *(*(marks + 0) + c);
    }
    int bestStudent = 1; // student 1 starts as top student
    cout << "\nStudent totals:" << endl;
    cout << "student 1 total: " << bestTotal << endl;

    // check remaining students
    for (int r = 1; r < rows; r++) {
        int currentTotal = 0;
        for (int c = 0; c < cols; c++) {
            currentTotal += *(*(marks + r) + c);
        }
        cout << "student " << (r + 1) << " total: " << currentTotal << endl;

        //using > sp first student remain in case of a tie
        if (currentTotal > bestTotal) {
            bestTotal = currentTotal;
            bestStudent = r + 1;
        }
    }
    cout << "Top student: " << bestStudent << " with total: " << bestTotal << endl;
    // 6 deallocateing memory
    // delete each row
    for (int r = 0; r < rows; r++) {
        delete[] marks[r];
    }
    // deleting the array of pointers
    delete[] marks;
    // setting to nullptr to avoid dangling pointer
    marks = nullptr;
    return 0;
}