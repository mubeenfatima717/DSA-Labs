#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// avl node structure
struct node {
    int key;
    int height;
    node *left, *right;
    node(int k) {
        key = k;
        height = 1;
        left = right = nullptr;
    }
};

// helper functions for height and balance factor
int get_height(node* n) {
    return n ? n->height : 0;
}

int get_balance(node* n) {
    return n ? get_height(n->left) - get_height(n->right) : 0;
}

// right rotation for balance restoration
node* right_rotate(node* y) {
    node* x = y->left;
    node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + max(get_height(y->left), get_height(y->right));
    x->height = 1 + max(get_height(x->left), get_height(x->right));

    return x;
}

// left rotation for balance restoration
node* left_rotate(node* x) {
    node* y = x->right;
    node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + max(get_height(x->left), get_height(x->right));
    y->height = 1 + max(get_height(y->left), get_height(y->right));

    return y;
}

// insert key and rebalance avl tree automatically
node* insert(node* root, int key) {
    if (!root) return new node(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root;
    }

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);

    // left left case
    if (balance > 1 && key < root->left->key)
        return right_rotate(root);

    // right right case
    if (balance < -1 && key > root->right->key)
        return left_rotate(root);

    // left right case
    if (balance > 1 && key > root->left->key) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // right left case
    if (balance < -1 && key < root->right->key) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

// find minimum value node for deletion
node* min_node(node* curr) {
    while (curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

// delete key and rebalance avl tree automatically
node* delete_node(node* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = delete_node(root->left, key);
    } else if (key > root->key) {
        root->right = delete_node(root->right, key);
    } else {
        if (!root->left || !root->right) {
            node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            node* temp = min_node(root->right);
            root->key = temp->key;
            root->right = delete_node(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);

    // left left case
    if (balance > 1 && get_balance(root->left) >= 0)
        return right_rotate(root);

    // left right case
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    // right right case
    if (balance < -1 && get_balance(root->right) <= 0)
        return left_rotate(root);

    // right left case
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

// sideways tree printer to visualize balance
void print_preorder(node* root) {
    if (!root) return;
    cout << root->key << "      ";
    print_preorder(root->left);
    print_preorder(root->right);
}

// retrieve top k elements based on criteria (max or min)
void get_top_k(node* root, int k, const string& criteria, vector<int>& res) {
    if (!root || res.size() >= k) return;

    if (criteria == "max") {
        get_top_k(root->right, k, criteria, res);
        if (res.size() < k) res.push_back(root->key);
        get_top_k(root->left, k, criteria, res);
    } else {
        get_top_k(root->left, k, criteria, res);
        if (res.size() < k) res.push_back(root->key);
        get_top_k(root->right, k, criteria, res);
    }
}

int main() {
    node* root = nullptr;
    vector<int> elements = {10, 20, 30, 40, 50, 25};

    cout << "inserting elements into avl tree:\n";
    for (int val : elements) {
        cout << "\ninserted " << val << ":\n";
        root = insert(root, val);
        print_preorder(root);
    }

    int k = 3;
    string criteria = "max";
    vector<int> top_k;
    get_top_k(root, k, criteria, top_k);

    cout << "\nquery: top " << k << " elements (" << criteria << "):\n";
    for (int val : top_k) {
        cout << val << " ";
    }
    cout << "\n";

    cout << "\ndeleting top " << k << " elements from avl tree:\n";
    for (int val : top_k) {
        cout << "\ndeleted " << val << ":\n";
        root = delete_node(root, val);
        print_preorder(root);
    }

    return 0;
}