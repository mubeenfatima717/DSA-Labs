#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// node representation for the huffman tree
struct node {
    char ch;
    int freq;
    node *left, *right;
    node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};
void print_preorder(node* root, string code) {
    if (!root) return;

    // print character and its binary code cleanly
    if (!root->left && !root->right) {
        cout << root->ch << " : " << code << "\n";
    }

    print_preorder(root->left, code + "0");
    print_preorder(root->right, code + "1");
}

// comparator to maintain min-heap order by frequency
struct cmp {
    bool operator()(node* a, node* b) {
        return a->freq > b->freq;
    }
};


int main() {
    string s = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    int n = s.size();

    // min-heap priority queue
    priority_queue<node*, vector<node*>, cmp> pq;

    // insert all characters and frequencies
    for (int i = 0; i < n; i++) {
        pq.push(new node(s[i], f[i]));
    }

    // build tree by merging lowest frequency nodes
    while (pq.size() > 1) {
        node* left = pq.top(); 
        pq.pop();
        node* right = pq.top(); 
        pq.pop();

        // create internal node with combined frequency
        node* parent = new node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    // root node remains in heap
    node* root = pq.top();

    // traverse and print codes in preorder
    print_preorder(root, "");

    return 0;
}