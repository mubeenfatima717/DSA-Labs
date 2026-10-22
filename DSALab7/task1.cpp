#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>
using namespace std;

// binary tree node struct for char
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// 1. generate binary tree from given nested string representation
Node* buildTreeFromString(const string& s, int& index) {
    // stop if end of string or closing bracket or comma
    if (index >= s.length() || s[index] == ')' || s[index] == ',') {
        return nullptr;
    }

    // read current node character
    char val = s[index++];
    Node* root = new Node(val);

    // check if node has children enclosed in parentheses
    if (index < s.length() && s[index] == '(') {
        index++; // skip '('

        // parse left child
        root->left = buildTreeFromString(s, index);

        // check for comma separating left and right children
        if (index < s.length() && s[index] == ',') {
            index++; // skip ','
            // parse right child
            root->right = buildTreeFromString(s, index);
        }

        // skip closing parenthesis ')'
        if (index < s.length() && s[index] == ')') {
            index++;
        }
    }

    return root;
}

// 2. recursive preorder traversal (root -> left -> right)
void preorderRecursive(Node* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->data << " ";
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

// 3. iterative inorder traversal using stack as linear adt (left -> root -> right)
void inorderIterative(Node* root) {
    stack<Node*> st;
    Node* curr = root;

    while (curr != nullptr || !st.empty()) {
        // reach the leftmost node of current node
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        // curr must be null at this point
        curr = st.top();
        st.pop();

        cout << curr->data << " ";

        // now visit right subtree
        curr = curr->right;
    }
}

// 4. iterative postorder traversal using two stacks (left -> right -> root)
void postorderIterative(Node* root) {
    if (root == nullptr) {
        return;
    }

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top();
        s1.pop();
        s2.push(curr);

        // push left and right children to first stack
        if (curr->left != nullptr) {
            s1.push(curr->left);
        }
        if (curr->right != nullptr) {
            s1.push(curr->right);
        }
    }

    // print all elements from second stack
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// 5. validate tree string without constructing the tree
bool validateTreeString(const string& s) {
    if (s.empty()) {
        return true;
    }

    stack<int> commaTracker; // count of commas inside current bracket pair

    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];

        if (ch == '(') {
            // open bracket must be preceded by node character
            if (i == 0 || (!isalnum(s[i - 1]) && s[i - 1] != ')' && s[i - 1] != ',')) {
                return false;
            }
            commaTracker.push(0);
        }
        else if (ch == ',') {
            // comma must exist inside brackets
            if (commaTracker.empty()) {
                return false;
            }
            commaTracker.top()++;
            // a binary tree node cannot have more than 1 comma (max 2 children)
            if (commaTracker.top() > 1) {
                return false;
            }
        }
        else if (ch == ')') {
            // closing bracket must have matching opening bracket
            if (commaTracker.empty()) {
                return false;
            }
            commaTracker.pop();
        }
    }

    // all brackets must be balanced
    return commaTracker.empty();
}

// 6a. calculate height of tree recursively
int calculateHeight(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max(calculateHeight(root->left), calculateHeight(root->right));
}

// 6b. calculate and display depth of each node recursively
void printNodeDepths(Node* root, int currentDepth) {
    if (root == nullptr) {
        return;
    }
    cout << "node '" << root->data << "' -> depth: " << currentDepth << endl;
    printNodeDepths(root->left, currentDepth + 1);
    printNodeDepths(root->right, currentDepth + 1);
}

// 7. bst node and operations for integer sequence
struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

// insert into bst
BSTNode* insertBST(BSTNode* root, int val) {
    if (root == nullptr) {
        return new BSTNode(val);
    }
    if (val < root->val) {
        root->left = insertBST(root->left, val);
    }
    else if (val > root->val) {
        root->right = insertBST(root->right, val);
    }
    return root;
}

// inorder traversal of bst (prints in sorted order)
void inorderBST(BSTNode* root) {
    if (root == nullptr) {
        return;
    }
    inorderBST(root->left);
    cout << root->val << " ";
    inorderBST(root->right);
}

int main() {
    string treeString = "a(b(d,e),c(,f(g,)))";

    cout << "input tree string: " << treeString << endl << endl;

    // 5. validate tree string without building tree
    cout << "5. string validation check:" << endl;
    if (validateTreeString(treeString)) {
        cout << "string is a valid binary tree representation." << endl;
    } else {
        cout << "string is invalid." << endl;
    }
    cout << endl;

    // 1. build binary tree from string
    int parseIndex = 0;
    Node* root = buildTreeFromString(treeString, parseIndex);
    cout << "1. binary tree constructed successfully from string." << endl << endl;

    // 2. preorder recursive
    cout << "2. preorder traversal (recursive):" << endl;
    preorderRecursive(root);
    cout << endl << endl;

    // 3. inorder iterative using stack
    cout << "3. inorder traversal (iterative using stack):" << endl;
    inorderIterative(root);
    cout << endl << endl;

    // 4. postorder iterative using stack
    cout << "4. postorder traversal (iterative using stack):" << endl;
    postorderIterative(root);
    cout << endl << endl;

    // 6. height and depths
    cout << "6. tree height & node depths:" << endl;
    cout << "total height of tree: " << calculateHeight(root) << endl;
    cout << "depth of individual nodes:" << endl;
    printNodeDepths(root, 0);
    cout << endl;

    // 7. bst from integer sequence
    cout << "7. bst from sequence [50, 30, 70, 20, 40, 60, 80]:" << endl;
    int bstValues[] = { 50, 30, 70, 20, 40, 60, 80 };
    int totalValues = sizeof(bstValues) / sizeof(bstValues[0]);

    BSTNode* bstRoot = nullptr;
    for (int i = 0; i < totalValues; i++) {
        bstRoot = insertBST(bstRoot, bstValues[i]);
    }
    cout << "inorder traversal of constructed bst (sorted):" << endl;
    inorderBST(bstRoot);
    cout << endl;
    return 0;
}