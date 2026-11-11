/*
design explanation:
1. binary search tree (bst) for student records:
   we use a bst because roll numbers are unique numbers. it allows fast searching, sorted display using inorder traversal, and avoids linear searching through an array.

2. stack for search history:
   we use a stack because search history must follow last-in first-out (lifo). the most recently searched roll number stays at the top.

time complexity comments:
- adding a student (insertion):
  best/average case: o(log n) when the bst is balanced.
  worst case: o(n) if the roll numbers are entered in sorted order (tree becomes like a linked list).

- searching a student:
  best/average case: o(log n).
  worst case: o(n) for an unbalanced bst.
*/

#include <iostream>
#include <string>

using namespace std;

// bst node to store student records
struct student {
    int roll_no;
    string name;
    student* left;
    student* right;
    student(int n, string s) {
        roll_no = n;
        name = s;
        left = right = nullptr;
    }
};

// custom stack node for search history without stl
struct history_node {
    int roll_no;
    history_node* next;
    history_node(int n) {
        roll_no = n;
        next = nullptr;
    }
};

// push searched roll number onto stack
void push_history(history_node*& top, int n) {
    history_node* newnode = new history_node(n);
    newnode->next = top;
    top = newnode;
}

// pop and return most recent roll number from stack
int pop_history(history_node*& top) {
    if (top == nullptr) return -1;
    int val = top->roll_no;
    history_node* temp = top;
    top = top->next;
    delete temp;
    return val;
}

// insert student into bst and reject duplicates
student* insertion(int n, string s, student* head) {
    if (head == nullptr) {
        return new student(n, s);
    }

    if (n == head->roll_no) {
        cout << "roll number already exists. duplicate rejected.\n";
        return head;
    } else if (n < head->roll_no) {
        head->left = insertion(n, s, head->left);
    } else {
        head->right = insertion(n, s, head->right);
    }

    return head;
}

// search student in bst by roll number
student* search_bst(int n, student* stu) {
    if (stu == nullptr) return nullptr;
    if (n == stu->roll_no) return stu;
    if (n < stu->roll_no) return search_bst(n, stu->left);
    return search_bst(n, stu->right);
}

// display all students in ascending order of roll number
void print_all(student* stu) {
    if (stu == nullptr) return;
    print_all(stu->left);
    cout << "roll no: " << stu->roll_no << " | name: " << stu->name << "\n";
    print_all(stu->right);
}

// clean up bst memory
void free_tree(student* root) {
    if (root == nullptr) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
}

// clean up stack memory
void free_stack(history_node*& top) {
    while (top != nullptr) {
        history_node* temp = top;
        top = top->next;
        delete temp;
    }
}

int main() {
    student* root = nullptr;
    history_node* history_top = nullptr;

    int choice = 0;

    // repeating menu loop
    while (choice != 5) {
        cout << "\nstudent help desk menu:\n";
        cout << "1. enter students\n";
        cout << "2. search a student\n";
        cout << "3. print all students\n";
        cout << "4. most recent search history\n";
        cout << "5. exit\n";
        cout << "enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int count;
                cout << "enter number of students you want to add: ";
                cin >> count;
                for (int i = 1; i <= count; i++) {
                    int n;
                    string s;
                    cout << "enter student " << i << " name: ";
                    cin >> s;
                    cout << "enter roll number: ";
                    cin >> n;
                    root = insertion(n, s, root);
                }
                break;
            }

            case 2: {
                if (root == nullptr) {
                    cout << "no students registered yet.\n";
                    break;
                }
                int search_roll;
                cout << "enter roll number to search: ";
                cin >> search_roll;

                student* found = search_bst(search_roll, root);
                if (found != nullptr) {
                    cout << "roll number found.\n";
                    cout << "student name: " << found->name << "\n";
                    push_history(history_top, search_roll);
                } else {
                    cout << "roll number not found.\n";
                }
                break;}
            case 3: {
                if (root == nullptr) {
                    cout << "no records to display.\n";
                } else {
                    cout << "\nregistered students (sorted by roll no):\n";
                    print_all(root);}
                break; }
            case 4: {
                int recent = pop_history(history_top);
                if (recent == -1) {
                    cout << "no search history available.\n";
                } else {
                    cout << "recently searched roll number: " << recent << "\n"; }
                break;   }
            case 5: {
                cout << "exiting program and releasing memory.\n";
                free_tree(root);
                free_stack(history_top);
                break; }
            default:
                cout << "invalid choice. please enter 1 to 5.\n";
                break; } }
    return 0;
}