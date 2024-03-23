#include <iostream>
using std::cout, std::string;

// StringStartA function
// Accept input string
// accept a(a|b)*
bool stringStartA(const string &);

int main() {
  string s = "ba";
  (stringStartA(s)) ? cout << "Accepted\n" : cout << "Rejected\n";
  return 0;
}

// Define of function
bool stringStartA(const string &inputString) {
  // The state of FM
  int state = 0;
  for (int i = 0; i < inputString.size(); ++i) {
    char inputChar = inputString[i];
    switch (state) {
    case 0:
      if (inputChar == 'a') {
        state = 1;
      } else {
        state = 3;
      }
      break;
    case 1:
      if (inputChar != 'a' && inputChar != 'b') {
        state = 3;
      }
    default:
      break;
    }
  }
  return (state == 1);
}
