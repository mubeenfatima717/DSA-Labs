#include <iostream>
#include <string>
using namespace std;
struct Node {
    char data;
    Node* next;
    Node(char val) {
        data = val;
        next = nullptr;
    }
};
//linked stack class
class Stack {
private:
    Node* topNode;
public:
    Stack() {
        topNode = nullptr;
    }
    // destructor
    ~Stack() {
        clearStack();
    }
    // check if stack has no elements
    bool isEmpty() {
        return topNode == nullptr;
    }
    // push character onto top of stack
    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }
    // removing character from top and delete node
    void pop() {
        if (isEmpty()) {
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
    // returning top char 
    char top() {
        if (isEmpty()) {
            return '\0';
        }
        return topNode->data;
    }
    // removeing all nodes and releaseing memory
    void clearStack() {
        while (!isEmpty()) {
            pop();
        }
    }
    // displaying current contents of stack
    void displayStack() {
        Node* temp = topNode;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};
// bracket matching
bool isMatching(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '[' && close == ']') return true;
    if (open == '{' && close == '}') return true;
    return false;
}
// process expression and checking bracket balance
bool checkBalance(string expr) {
    Stack s;
    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        // push opening brackets
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);} 
        // compareing racket 
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.isEmpty()) {
                return false;  }
            if (!isMatching(s.top(), ch)) {
                return false; }
            s.pop();}}
    // stack must be empty for expression to be balanced
    return s.isEmpty();
}
int main() {
    //test cases
    string tests[] = {
        "(A+B)",
        "{A+[B*C]}",
        "(A+B]",
        "((A+B)",
        "{[()]}",
        "A+B*C",
        "([A+B])"
    };
    int n = sizeof(tests) / sizeof(tests[0]);
    // testing and displaying
    for (int i = 0; i < n; i++) {
        cout << tests[i] << " -> ";
        if (checkBalance(tests[i])) {
            cout << "Balanced" << endl;
        } else {
            cout << "Not Balanced" << endl;} }
    return 0;
}