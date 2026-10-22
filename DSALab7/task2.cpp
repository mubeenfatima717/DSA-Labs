#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// student record node definition
struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;

    Student(int id, string n, float gpa) {
        studentID = id;
        name = n;
        GPA = gpa;
        left = nullptr;
        right = nullptr;
    }
};

// insert a new student record into the bst ordered by student id
Student* insert(Student* root, int id, string name, float gpa) {
    if (root == nullptr) {
        return new Student(id, name, gpa);
    }

    if (id < root->studentID) {
        root->left = insert(root->left, id, name, gpa);
    } else if (id > root->studentID) {
        root->right = insert(root->right, id, name, gpa);
    } else {
        cout << "record with student id " << id << " already exists." << endl;
    }

    return root;
}

// search for student details by id
Student* search(Student* root, int id) {
    if (root == nullptr || root->studentID == id) {
        return root;
    }

    if (id < root->studentID) {
        return search(root->left, id);
    }
    return search(root->right, id);
}

// helper function to find minimum node (inorder successor)
Student* findMin(Student* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// delete a student record by id handling 0, 1, and 2 children cases
Student* deleteStudent(Student* root, int id) {
    if (root == nullptr) {
        return nullptr;
    }

    if (id < root->studentID) {
        root->left = deleteStudent(root->left, id);
    } else if (id > root->studentID) {
        root->right = deleteStudent(root->right, id);
    } else {
        // case 1: leaf node (no children)
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // case 2: one child
        else if (root->left == nullptr) {
            Student* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Student* temp = root->left;
            delete root;
            return temp;
        }
        // case 3: two children
        else {
            Student* successor = findMin(root->right);
            root->studentID = successor->studentID;
            root->name = successor->name;
            root->GPA = successor->GPA;
            root->right = deleteStudent(root->right, successor->studentID);
        }
    }
    return root;
}

// inorder traversal: prints students sorted by student id
void inorder(Student* root) {
    if (root == nullptr) {
        return;
    }
    inorder(root->left);
    cout << "id: " << setw(4) << root->studentID 
         << " | name: " << setw(10) << left << root->name 
         << " | gpa: " << fixed << setprecision(2) << root->GPA << endl;
    inorder(root->right);
}

// analytical feature 1: count total students recursively
int countStudents(Student* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countStudents(root->left) + countStudents(root->right);
}

// analytical feature 2: find students with highest and lowest gpa
void findGPALimits(Student* root, Student*& maxStudent, Student*& minStudent) {
    if (root == nullptr) {
        return;
    }

    if (maxStudent == nullptr || root->GPA > maxStudent->GPA) {
        maxStudent = root;
    }
    if (minStudent == nullptr || root->GPA < minStudent->GPA) {
        minStudent = root;
    }

    findGPALimits(root->left, maxStudent, minStudent);
    findGPALimits(root->right, maxStudent, minStudent);
}

// analytical feature 3: display students with gpa above threshold
void displayAboveThreshold(Student* root, float threshold) {
    if (root == nullptr) {
        return;
    }
    displayAboveThreshold(root->left, threshold);
    if (root->GPA >= threshold) {
        cout << "id: " << setw(4) << root->studentID 
             << " | name: " << setw(10) << left << root->name 
             << " | gpa: " << fixed << setprecision(2) << root->GPA << endl;
    }
    displayAboveThreshold(root->right, threshold);
}

int main() {
    Student* root = nullptr;

    cout << "=========================================" << endl;
    cout << "   student record management system      " << endl;
    cout << "=========================================" << endl << endl;

    // 1. insert student records
    cout << "1. inserting sample student records..." << endl;
    root = insert(root, 105, "Ali", 3.45);
    root = insert(root, 102, "Sara", 3.85);
    root = insert(root, 108, "Hamza", 2.90);
    root = insert(root, 101, "Zain", 3.10);
    root = insert(root, 104, "Ayesha", 3.95);
    root = insert(root, 107, "Bilal", 2.50);
    cout << "records inserted successfully." << endl << endl;

    // 2. inorder traversal (sorted by id)
    cout << "2. all student records (inorder traversal sorted by id):" << endl;
    inorder(root);
    cout << endl;

    // 3. search for a student
    int searchID = 104;
    cout << "3. searching for student id " << searchID << ":" << endl;
    Student* found = search(root, searchID);
    if (found != nullptr) {
        cout << "found: id: " << found->studentID 
             << ", name: " << found->name 
             << ", gpa: " << found->GPA << endl;
    } else {
        cout << "student with id " << searchID << " not found." << endl;
    }
    cout << endl;

    // 4. delete a record
    int deleteID = 105;
    cout << "4. deleting student id " << deleteID << " (node with two children):" << endl;
    root = deleteStudent(root, deleteID);
    cout << "inorder traversal after deletion:" << endl;
    inorder(root);
    cout << endl;

    // 5. analytical features
    cout << "5. analytical reports:" << endl;
    cout << "total registered students: " << countStudents(root) << endl << endl;

    Student* maxStudent = nullptr;
    Student* minStudent = nullptr;
    findGPALimits(root, maxStudent, minStudent);

    if (maxStudent != nullptr && minStudent != nullptr) {
        cout << "highest gpa: " << maxStudent->GPA << " (" << maxStudent->name << ", id: " << maxStudent->studentID << ")" << endl;
        cout << "lowest gpa:  " << minStudent->GPA << " (" << minStudent->name << ", id: " << minStudent->studentID << ")" << endl;
    }
    cout << endl;

    float threshold = 3.0;
    cout << "students with gpa >= " << threshold << ":" << endl;
    displayAboveThreshold(root, threshold);
    cout << endl;
    return 0;
}