#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// func to check if string is palindrome 
bool isPalindrome(string str) {
    int left = 0;
    int right = str.length() - 1;
    while (left < right) {
        // skiping non alphanumeric chars
        while (left < right && !isalnum(str[left])) {
            left++;
        }
        while (left < right && !isalnum(str[right])) {
            right--;
        }
        // comparing chars by converting to lowercase
        if (tolower(str[left]) != tolower(str[right])) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    string text;
    cout << "Enter a string: ";
    getline(cin, text);
    if (isPalindrome(text)) {
        cout << "string is a palindrome." << endl;
    } else {
        cout << "string is not a palindrome." << endl;
    }
    return 0;
}