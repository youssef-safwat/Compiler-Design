#include <iostream>
using std::string, std::cout;
// RealNumber function
// Accept StringInput
// Return accepted D+.D+
bool realNumber(const string &);

int main() {
  string s = "0.53";
  (realNumber(s)) ? cout << "Accepted\n" : cout << "Rejected\n";
  return 0;
}

// Define realNumber function
bool realNumber(const string &inputString) {
  // FM state
  int state = 0;
  for (char inputChar : inputString) {
    switch (state) {
    case 0:
      if (isdigit(inputChar)) {
        state = 1;
      } else {
        state = 4;
      }
      break;
    case 1:
      if (isdigit(inputChar)) {
        state = 1;
      } else if (inputChar == '.') {
        state = 2;
      } else {
        state = 4;
      }
      break;
    case 2:
      if (isdigit(inputChar)) {
        state = 3;
      } else {
        state = 4;
      }
      break;
    case 3:
      if (!isdigit(inputChar)) {
        state = 4;
      }
      break;
    default:
      break;
    }
  }
  return state == 3;
}
