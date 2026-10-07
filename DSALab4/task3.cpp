#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// node structure for doubly linked list bit storage
struct BitNode {
    int bit;
    BitNode* next;
    BitNode* prev;
};

// doubly linked list for binary numbers
class BinaryDLL {
public:
    BitNode* head;
    BitNode* tail;
    int length;

    // constructor
    BinaryDLL() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // append bit at tail
    void appendBit(int b) {
        BitNode* newNode = new BitNode();
        newNode->bit = b;
        newNode->next = nullptr;
        newNode->prev = tail;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    // prepend bit at head
    void prependBit(int b) {
        BitNode* newNode = new BitNode();
        newNode->bit = b;
        newNode->prev = nullptr;
        newNode->next = head;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    // clear all nodes to free memory
    void clear() {
        BitNode* curr = head;
        while (curr != nullptr) {
            BitNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // store binary string padded to 8-bit blocks
    void storeBinary(string binaryStr) {
        clear();
        int pad = 8 - (binaryStr.length() % 8);
        if (pad != 8) {
            binaryStr = string(pad, '0') + binaryStr;
        }
        for (char c : binaryStr) {
            if (c == '0' || c == '1') {
                appendBit(c - '0');
            }
        }
    }

    // display binary number grouped in 8-bit blocks
    void display() {
        if (head == nullptr) {
            cout << "00000000" << endl;
            return;
        }
        BitNode* curr = head;
        int count = 0;
        while (curr != nullptr) {
            cout << curr->bit;
            count++;
            if (count % 8 == 0 && curr->next != nullptr) {
                cout << " ";
            }
            curr = curr->next;
        }
        cout << endl;
    }

    // compute 1s complement
    BinaryDLL onesComplement() {
        BinaryDLL result;
        BitNode* curr = head;
        while (curr != nullptr) {
            result.appendBit(curr->bit == 0 ? 1 : 0);
            curr = curr->next;
        }
        return result;
    }

    // static binary addition of two dll numbers
    static BinaryDLL add(BinaryDLL num1, BinaryDLL num2) {
        BinaryDLL result;
        BitNode* p1 = num1.tail;
        BitNode* p2 = num2.tail;
        int carry = 0;
        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int sum = carry;
            if (p1 != nullptr) {
                sum += p1->bit;
                p1 = p1->prev;
            }
            if (p2 != nullptr) {
                sum += p2->bit;
                p2 = p2->prev;
            }
            result.prependBit(sum % 2);
            carry = sum / 2;
        }
        // pad result to multiple of 8 bits
        int pad = 8 - (result.length % 8);
        if (pad != 8) {
            for (int i = 0; i < pad; i++) {
                result.prependBit(0);
            }
        }
        return result;
    }

    // compute 2s complement (1s complement + 1)
    BinaryDLL twosComplement() {
        BinaryDLL ones = onesComplement();
        BinaryDLL one;
        one.storeBinary("1");
        return BinaryDLL::add(ones, one);
    }

    // binary multiplication using repeated addition and shifting
    static BinaryDLL multiply(BinaryDLL num1, BinaryDLL num2) {
        BinaryDLL result;
        result.storeBinary("0");
        BitNode* p2 = num2.tail;
        int shift = 0;
        while (p2 != nullptr) {
            if (p2->bit == 1) {
                BinaryDLL shiftedNum1;
                BitNode* p1 = num1.head;
                while (p1 != nullptr) {
                    shiftedNum1.appendBit(p1->bit);
                    p1 = p1->next;
                }
                for (int i = 0; i < shift; i++) {
                    shiftedNum1.appendBit(0);
                }
                result = BinaryDLL::add(result, shiftedNum1);
            }
            shift++;
            p2 = p2->prev;
        }
        return result;
    }

    // convert binary dll to decimal
    long long toDecimal() {
        long long decimalVal = 0;
        BitNode* curr = head;
        while (curr != nullptr) {
            decimalVal = (decimalVal * 2) + curr->bit;
            curr = curr->next;
        }
        return decimalVal;
    }

    // destructor to free memory
    ~BinaryDLL() {
        clear();
    }
};

int main() {
    BinaryDLL bin1, bin2;
    int choice;
    string s1, s2;

    do {
        cout << "\n1. Store Binary Numbers" << endl;
        cout << "2. Display Stored Numbers" << endl;
        cout << "3. 1's Complement" << endl;
        cout << "4. 2's Complement" << endl;
        cout << "5. Binary Addition" << endl;
        cout << "6. Binary Multiplication" << endl;
        cout << "7. Convert to Decimal" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter first binary number: ";
                cin >> s1;
                bin1.storeBinary(s1);
                cout << "Enter second binary number: ";
                cin >> s2;
                bin2.storeBinary(s2);
                cout << "numbers stored successfully in 8-bit blocks." << endl;
                break;
            case 2:
                cout << "Number 1: ";
                bin1.display();
                cout << "Number 2: ";
                bin2.display();
                break;
            case 3:
                cout << "1's complement of Number 1: ";
                bin1.onesComplement().display();
                cout << "1's complement of Number 2: ";
                bin2.onesComplement().display();
                break;
            case 4:
                cout << "2's complement of Number 1: ";
                bin1.twosComplement().display();
                cout << "2's complement of Number 2: ";
                bin2.twosComplement().display();
                break;
            case 5: {
                BinaryDLL sum = BinaryDLL::add(bin1, bin2);
                cout << "Addition result: ";
                sum.display();
                break;
            }
            case 6: {
                BinaryDLL product = BinaryDLL::multiply(bin1, bin2);
                cout << "Multiplication result: ";
                product.display();
                break;
            }
            case 7:
                cout << "Decimal value of Number 1: " << bin1.toDecimal() << endl;
                cout << "Decimal value of Number 2: " << bin2.toDecimal() << endl;
                break;
            case 8:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);
    return 0;
}