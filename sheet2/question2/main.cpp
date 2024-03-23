#include <iostream>
using namespace std;

// states enum for the given FM
enum states { s0, s1, s2 };

// divisibleBy3 function
// Accept stringInput
// Return true if the number divisible by 3
bool divisibleBy3(const string &);

int main() {

  char choice;
  do {
    string s;
    cout << "Please enter String of 1's and 0's: ";
    cin >> s;
    cout << ((divisibleBy3(s)) ? "Acccepted\n" : "Rejected\n");
    cout << "Press y/n to continue: ";
    cin >> choice;
  } while (choice == 'y');
  return 0;
}

// Define divisibleBy3 function
bool divisibleBy3(const string &stringInput) {
  // current state of FM
  int currState = s0;
  // Iterate for each character
  for (auto stringChar : stringInput) {
    switch (currState) {
    case s0:
      if (stringChar == '0') {
        currState = s0;
      } else {
        currState = s1;
      }
      break;
    case s1:
      if (stringChar == '1') {
        currState = s0;
      } else {
        currState = s2;
      }
      break;
    case s2:
      if (stringChar == '1') {
        currState = s2;
      } else {
        currState = s1;
      }
    default:
      break;
    }
  }
  return currState == s0;
}
