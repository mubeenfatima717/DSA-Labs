#include <iostream>

using namespace std;

// node structure
struct Node {
    int data;
    Node* next;
};

// linked list class
class LinkedList {
private:
    Node* head;

public:
    // constructor to initialize head to null
    LinkedList() {
        head = nullptr;
    }

    // 1 insert node at head
    void insertAtHead(int val) {
        Node* newNode = new Node();
        newNode->data = val;
        newNode->next = head;
        head = newNode;
        cout << "node with value " << val << " inserted at head." << endl;
    }

    // 2 inserting node at 3 position
    void insertAtThird(int val) {
        if (head == nullptr || head->next == nullptr) {
            cout << "list has fewer than 2 nodes. cannot insert at 3rd position." << endl;
            return;
        }

        Node* newNode = new Node();
        newNode->data = val;
        // insert after the second node
        newNode->next = head->next->next;
        head->next->next = newNode;
        cout << "node with value " << val << " inserted at 3rd position." << endl;
    }

    // 3 display=ing all nodes in the list
    void displayList() {
        if (head == nullptr) {
            cout << "list is empty -> NULL" << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // 4 deletimg the last node
    void deleteLast() {
        if (head == nullptr) {
            cout << "list is empty. nothing to delete." << endl;
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            cout << "single node deleted. list is now empty." << endl;
            return;
        }

        Node* temp = head;
        // traverse to the 2nd last node
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = nullptr;
        cout << "last node deleted successfully." << endl;
    }

    //5 count total no of nodes
    int countNodes() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    // 6 reverseing list 
    void reverseList() {
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next; // store next node
            current->next = prev;     // reverse pointer dir
            prev = current;           // move prev forward
            current = nextNode;       // move cur forward
        }
        head = prev;
        cout << "list reversed successfully." << endl;
    }

    // 7 searching for a value in the list
    void searchValue(int val) {
        Node* temp = head;
        int position = 1;
        bool found = false;

        while (temp != nullptr) {
            if (temp->data == val) {
                cout << "value " << val << " found at position: " << position << endl;
                found = true;
                break;
            }
            temp = temp->next;
            position++;
        }

        if (!found) {
            cout << "value " << val << " not found in the list." << endl;
        }
    }

    // destructor to clean up remaining nodes
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }
};

int main() {
    LinkedList list;
    int choice, value;

    do {
        cout << "\n--- singly linked list menu ---" << endl;
        cout << "1. insert at head" << endl;
        cout << "2. insert at 3rd position" << endl;
        cout << "3. display list" << endl;
        cout << "4. delete last node" << endl;
        cout << "5. count nodes" << endl;
        cout << "6. reverse list" << endl;
        cout << "7. search value" << endl;
        cout << "8. exit" << endl;
        cout << "enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "enter value to insert: ";
                cin >> value;
                list.insertAtHead(value);
                break;
            case 2:
                cout << "enter value to insert at 3rd position: ";
                cin >> value;
                list.insertAtThird(value);
                break;
            case 3:
                cout << "current list: ";
                list.displayList();
                break;
            case 4:
                list.deleteLast();
                cout << "updated list: ";
                list.displayList();
                break;
            case 5:
                cout << "total nodes: " << list.countNodes() << endl;
                break;
            case 6:
                list.reverseList();
                cout << "updated list: ";
                list.displayList();
                break;
            case 7:
                cout << "enter value to search: ";
                cin >> value;
                list.searchValue(value);
                break;
            case 8:
                cout << "exiting program." << endl;
                break;
            default:
                cout << "invalid choice. try again." << endl;
        }
    } while (choice != 8);

    return 0;
}