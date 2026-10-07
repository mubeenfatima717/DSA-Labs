#include <iostream>
using namespace std;

// node structure for circular linked list
struct Node {
    int personID;
    Node* next;
};

// class for josephus problem simulation
class JosephusCircle {
private:
    Node* head;

public:
    // constructor
    JosephusCircle() {
        head = nullptr;
    }

    // create circular linked list of n people
    void createCircle(int n) {
        if (n <= 0) return;
        head = new Node();
        head->personID = 1;
        head->next = head; // points to itself initially
        Node* prev = head;
        for (int i = 2; i <= n; i++) {
            Node* newNode = new Node();
            newNode->personID = i;
            newNode->next = head; // link back to head to maintain circle
            prev->next = newNode;
            prev = newNode;
        }
    }

    // run elimination process
    void eliminate(int k) {
        if (head == nullptr) {
            cout << "circle is empty." << endl;
            return;
        }
        Node* current = head;
        Node* prev = nullptr;
        cout << "\nelimination order:" << endl;

        // continue until only one person remains
        while (current->next != current) {
            // move k-1 steps forward to reach the k-th person
            for (int count = 1; count < k; count++) {
                prev = current;
                current = current->next;
            }

            // if prev is not set (e.g. when k=1)
            if (prev == nullptr) {
                prev = current;
                while (prev->next != current) {
                    prev = prev->next;
                }
            }

            // display eliminated person
            cout << "person " << current->personID << " eliminated" << endl;

            // update links to remove k-th person
            prev->next = current->next;
            if (current == head) {
                head = current->next;
            }
            Node* toDelete = current;
            current = current->next; // resume counting from next person
            delete toDelete;         // free memory
        }
        // display last remaining person
        head = current;
        cout << "\nsurvivor: person " << head->personID << endl;
        // free survivor node memory
        delete head;
        head = nullptr;
    }

    // destructor to clean up memory in case list is not empty
    ~JosephusCircle() {
        if (head == nullptr) return;
        Node* current = head;
        while (current->next != head) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        delete current;
        head = nullptr;
    }
};

int main() {
    int n, k;
    cout << "enter number of people (n): ";
    cin >> n;
    cout << "enter step count (k): ";
    cin >> k;
    if (n <= 0 || k <= 0) {
        cout << "invalid input. n and k must be positive integers." << endl;
        return 1;
    }
    JosephusCircle game;
    game.createCircle(n);
    game.eliminate(k);

    return 0;
}