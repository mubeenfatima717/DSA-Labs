#include <iostream>
#include <string>
#include <cctype>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(T val) {
        data = val;
        next = nullptr;
    }
};

// linked stack class
template <typename T>
class Stack {
private:
    Node<T>* topNode;

public:
    Stack() {
        topNode = nullptr;
    }

    // destructo
    ~Stack() {
        clear();
    }
    // check if stack is empty
    bool isEmpty() {
        return topNode == nullptr;
    }
    // insert element onto top of stack
    void push(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = topNode;
        topNode = newNode;
    }
    // remove top element and delete node
    void pop() {
        if (isEmpty()) return;
        Node<T>* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
    // return top element without removing
    T top() {
        if (isEmpty()) return T();
        return topNode->data;
    }
    // remove all nodes from stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};
// return operator precedence
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}
// check if character is an arithmetic operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}
// convert infix expression to postfix notation
string infixToPostfix(string infix, bool &isValid) {
    Stack<char> opStack;
    string postfix = "";
    int openCount = 0;
    isValid = true;
    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        // skip whitespace
        if (isspace(ch)) continue;
        // handle multi-digit operands
        if (isdigit(ch)) {
            while (i < infix.length() && isdigit(infix[i])) {
                postfix += infix[i];
                i++;
            }
            postfix += " ";
            i--;
        }
        // push opening parenthesis
        else if (ch == '(') {
            opStack.push(ch);
            openCount++;
        }
        // handle closing parenthesis
        else if (ch == ')') {
            if (openCount <= 0) {
                isValid = false;
                return "";
            }
            while (!opStack.isEmpty() && opStack.top() != '(') {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            if (!opStack.isEmpty()) {
                opStack.pop();
                openCount--;
            }
        }
        // handle arithmetic operators by precedence
        else if (isOperator(ch)) {
            while (!opStack.isEmpty() && opStack.top() != '(' && 
                   getPrecedence(opStack.top()) >= getPrecedence(ch)) {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            opStack.push(ch);
        }
        // invalid character detected
        else {
            isValid = false;
            return "";}}
    // check for remaining unmatched parentheses
    if (openCount != 0) {
        isValid = false;
        return "";
    }
    // pop remaining operators from stack
    while (!opStack.isEmpty()) {
        if (opStack.top() == '(') {
            isValid = false;
            return "";
        }
        postfix += opStack.top();
        postfix += " ";
        opStack.pop();
    }
    return postfix;
}
// evaluate postfix expression using stack
int evaluatePostfix(string postfix, bool &error, string &errorMsg) {
    Stack<int> valStack;
    error = false;
    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];
        if (isspace(ch)) continue;
        // read full integer operand and push to stack
        if (isdigit(ch)) {
            int num = 0;
            while (i < postfix.length() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            valStack.push(num);
            i--;
        }
        // pop two operands and apply operator
        else if (isOperator(ch)) {
            if (valStack.isEmpty()) {
                error = true;
                errorMsg = "invalid expression";
                return 0;
            }
            int val2 = valStack.top();
            valStack.pop();

            if (valStack.isEmpty()) {
                error = true;
                errorMsg = "invalid expression";
                return 0;
            }
            int val1 = valStack.top();
            valStack.pop();

            // detect division or modulus by zero
            if ((ch == '/' || ch == '%') && val2 == 0) {
                error = true;
                errorMsg = "division by zero";
                return 0;
            }

            int res = 0;
            if (ch == '+') res = val1 + val2;
            else if (ch == '-') res = val1 - val2;
            else if (ch == '*') res = val1 * val2;
            else if (ch == '/') res = val1 / val2;
            else if (ch == '%') res = val1 % val2;

            valStack.push(res);
        }
    }

    if (valStack.isEmpty()) {
        error = true;
        errorMsg = "empty expression";
        return 0;
    }

    int finalResult = valStack.top();
    valStack.pop();

    if (!valStack.isEmpty()) {
        error = true;
        errorMsg = "invalid expression";
        return 0;
    }

    return finalResult;
}
// helper function to process and display results
void processExpression(string expr) {
    cout << "infix:   " << expr << endl;
    if (expr.empty()) {
        cout << "error:   empty expression" << endl << endl;
        return;
    }
    bool isValid = true;
    string postfix = infixToPostfix(expr, isValid);
    if (!isValid) {
        cout << "error:   mismatched parentheses or invalid characters" << endl << endl;
        return;
    }
    cout << "postfix: " << postfix << endl;
    bool hasError = false;
    string errorMsg = "";
    int result = evaluatePostfix(postfix, hasError, errorMsg);
    if (hasError) {
        cout << "error:   " << errorMsg << endl;
    } else {
        cout << "result:  " << result << endl;
    }
    cout << endl;
}

int main() {
    // standard test cases from lab manual
    cout << "-- standard test cases --" << endl;
    processExpression("2 + 3 * 4");
    processExpression("(2 + 3) * 4");
    processExpression("10 + 2 * 6");
    processExpression("(10 + 2) * (6 - 3)");
    processExpression("20 / 5 + 3");

    // cases testing
    cout << "-- edge cases --" << endl;
    processExpression("((2 + 3) * (4 + 1))");  // nested parentheses
    processExpression("10 + 2 * 3 - 4 / 2");    // multiple operators
    processExpression("10 / (5 - 5)");          // division by zero
    processExpression("(2 + 3 * 4");            // mismatched parentheses
    processExpression("");                      // empty expression
    return 0;
}