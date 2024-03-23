#include<iostream>
using std::cout, std::string;

// identifier function
// Accept input string
// Accept (letter|_)(letter | digit | _)*
bool identifier(const string&);

int main() {
    string s = "a42_a";
    (identifier(s)) ? cout << "Accpected\n" : cout << "Rejected\n";
    return 0;
}

// Define of function
bool identifier(const string& inputString) {
    // The state of FM
    int state = 0;
    for(int i = 0; i < inputString.size(); ++i) {
        char inputChar = inputString[i];
        switch (state)
        {
        case 0:
            if(inputChar == '_' || isalpha(inputChar)) {
                state = 1;
            } else {
                state = 2;
            }
            break;
        case 1:
            if(inputChar != '_' && !isalnum(inputChar)) {
                state = 2;
            }
        default:
            break;
        }
    }
    return state == 1;
}
