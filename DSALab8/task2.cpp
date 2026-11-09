#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// basic node structure for singly linked list
struct node {
    int val;
    node* next;
    node(int x) {
        val = x;
        next = nullptr;
    }
};

// comparator to order heap by smallest value first
struct cmp {
    bool operator()(node* a, node* b) {
        return a->val > b->val;
    }
};

// function to merge k sorted lists using min heap
node* merge_k_lists(vector<node*>& lists) {
    priority_queue<node*, vector<node*>, cmp> pq;

    // insert starting node of each list into heap
    for (int i = 0; i < lists.size(); i++) {
        if (lists[i] != nullptr) {
            pq.push(lists[i]);
        }
    }

    node dummy(0);
    node* tail = &dummy;

    // repeatedly extract min node and push its next node
    while (!pq.empty()) {
        node* curr = pq.top();
        pq.pop();

        tail->next = curr;
        tail = tail->next;

        if (curr->next != nullptr) {
            pq.push(curr->next);
        }
    }

    return dummy.next;
}

// helper to print linked list elements
void print_list(node* head) {
    while (head != nullptr) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "null\n";
}

int main() {
    // creating 3 sorted test lists
    node* l1 = new node(1);
    l1->next = new node(4);
    l1->next->next = new node(5);

    node* l2 = new node(1);
    l2->next = new node(3);
    l2->next->next = new node(4);

    node* l3 = new node(2);
    l3->next = new node(6);

    vector<node*> lists = {l1, l2, l3};

    // display lists before merging
    cout << "before merge:\n";
    for (int i = 0; i < lists.size(); i++) {
        cout << "list " << i + 1 << ": ";
        print_list(lists[i]);
    }

    // merge all lists
    node* merged = merge_k_lists(lists);

    // display final sorted list after merging
    cout << "\nafter merge:\n";
    cout << "result: ";
    print_list(merged);

    return 0;
}