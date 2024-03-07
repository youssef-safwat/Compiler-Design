#include<iostream>
using namespace std;

// comment function
// Accept String
// "(L|D|\")*"
bool comment(const string&);


int main() {
    string s = "\"asdafwe\"32421f\"";
    cout << ((comment(s) ? "Accepted\n" : "Rejected\n"));
    return 0;
}

// Define of comment function
bool comment(const string& inputString) {
    // FM States
    int state = 0;
    for(char inputChar : inputString) {
        switch (state)
        {
        case 0:
            if(inputChar == '\"') {
                state = 1;
            } else {
                state = 4;
            }
            break;
        case 1:
            if(inputChar == '\"') {
                state = 3;
            } else if(isalnum(inputChar)) {
                state = 1;
            } else if(inputChar == '\\') {
                state = 2;
            } else {
                state = 4;
            }
            break;
        case 2:
            if(inputChar == '\"') {
                state = 1;
            } else {
                state = 4;
            }
            break;
        default:
            break;
        }
    }
    return state == 3;
}