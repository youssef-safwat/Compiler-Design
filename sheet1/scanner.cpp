#include "scanner.h"

// Constructor to open the file
scanner::scanner(const std::string& s) {
    f.open(s);
    // Check if file not opened
    if(!f) {
        std::cout << "File is not opened\n";
        exit(1);
    }
}

//  distractor to close the file
scanner::~scanner() {
    f.close();
}

// Define check_reserved function
token_t scanner::check_reserved(const std::string& s) {
    token_t t;
    if(s == "cin") {
        t._token = CIN_SY;
        t.lexemes = "cin";
    }
    else if(s == "cout") {
        t._token = COUT_SY;
        t.lexemes = "cout";
    }
    else {
        t._token = ID;
        t.lexemes = s;
    }
    return t;
}

// Define of get_token function
token_t scanner::get_tokens() {
    token_t t;
    char c;
    // Get the first character
    f.get(c);
    // Keep getting character while c is a space
    while (isspace(c) && !f.eof()) {
        f.get(c);
    }

    switch (c) {
        case '+':
            t._token = PLUS;
            t.lexemes = "+";
            break;
        case '*':
            t._token = MULTI;
            t.lexemes = "*";
            break;
        case '/':
            t._token = DIVISION_SY;
            t.lexemes = "/";
            break;
        case '^':
            t._token = POWER_SY;
            t.lexemes = "^";
            break;
        case '(':
            t._token = OPEN_PARANTHESES;
            t.lexemes = "(";
            break;
        case ')':
            t._token = CLOSE_PARANTHESES;
            t.lexemes = ")";
            break;
        case '<':
            t.lexemes += c;
            f.get(c);
            if (c == '<') {
                t._token = LL_SY;
                t.lexemes += c;
            } 
            else if(c == '=') {
                t._token = LE_SY;
                t.lexemes += c;
            }
            else if(c == '>') {
                t._token = NE_SY;
                t.lexemes += c;
            }
            else {
                t._token = L_SY;
                f.putback(c);
            }
            break;
        case '>':
        t.lexemes += c;
            f.get(c);
            if (c == '>') {
                t._token = GG_SY;
                t.lexemes += c;
            } 
            else if(c == '=') {
                t._token = GE_SY;
                t.lexemes += c;
            }
            else {
                t._token = G_SY;
                f.putback(c);
            }
            break;
        case '=':
            t.lexemes += c;
            f.get(c);
            if(c == '=') {
                t.lexemes += c;
                t._token = EE_SY;
            } else {
                t._token = E_SY;
                f.putback(c);
            }
        // Check if token is number or identifier
        default:
            if (isalpha(c)) {
                t.lexemes = c;
                while (isalnum(f.peek())) {
                    f.get(c);
                    t.lexemes += c;
                }
                return check_reserved(t.lexemes);
            } 
            else if (isdigit(c)) {
                // Check the integer number
                t.lexemes = c;
                while (isdigit(f.peek())) {
                    f.get(c);
                    t.lexemes += c;
                }
                // Check the real number
                if(f.peek() != '.') {
                    t._token = INTEGER;
                }
                else if(f.peek() == '.') {
                    t.lexemes += '.';
                    f.get(c);
                    // D+. is an error
                    if(!isdigit(f.peek())) {
                        t._token = ERROR_SY;
                    } 
                    else {
                        while(isdigit(f.peek())) {
                            f.get(c);
                            t.lexemes += c;
                        }
                        t._token = REAL;
                    }
                }
            } 
            // .D+ is accepted as a real number
            else if(c == '.') {
                t.lexemes = c;
                if(isdigit(f.peek())) {
                    while(isdigit(f.peek())) {
                        f.get(c);
                        t.lexemes += c;
                    }
                    t._token = REAL;
                }
                else {
                    t._token = ERROR_SY;
                }
            }
            else if (f.eof()) {
                t.lexemes = "end of file";
                t._token = _EOF_;
            }
    }
    return t;
}

// define of display_tokens function
void scanner::display_tokens() {
    token_t t = get_tokens();
    std::cout << "Toekn\t\t\tLexemes\n";
    std::cout << "----------------------------------\n";
    while(t._token != _EOF_) {
        // Switch to display each token
        switch (t._token)
        {
        case PLUS:
            std::cout << "PLUS\t\t\t" << t.lexemes << '\n';
            break;
        
        case MULTI:
            std::cout << "MULTI\t\t\t" << t.lexemes << '\n';
            break;
        
        case CIN_SY:
            std::cout << "CIN_SY\t\t\t" << t.lexemes << '\n';
            break;
        
        case COUT_SY:
            std::cout << "COUT_SY\t\t\t" << t.lexemes << '\n';
            break;
        
        case GG_SY:
            std::cout << "GG_SY\t\t\t" << t.lexemes << '\n';
            break;
        
        case LL_SY:
            std::cout << "LL_SY\t\t\t" << t.lexemes << '\n';
            break;
        case LE_SY:
            std::cout << "LE_SY\t\t\t" << t.lexemes << '\n';
            break;
        case L_SY:
            std::cout << "L_SY\t\t\t" << t.lexemes << '\n';
            break;
        case NE_SY:
            std::cout << "NE_SY\t\t\t" << t.lexemes << '\n';
            break;
        case G_SY:
            std::cout << "G_SY\t\t\t" << t.lexemes << '\n';
            break;
        
        case E_SY:
            std::cout << "E_SY\t\t\t" << t.lexemes << '\n';
            break;
        
        case EE_SY:
            std::cout << "EE_SY\t\t\t" << t.lexemes << '\n';
            break;
        
        case GE_SY:
            std::cout << "GE_SY\t\t\t" << t.lexemes << '\n';
            break;
        
        case OPEN_PARANTHESES:
            std::cout << "OPEN_PARANTHESES\t" << t.lexemes << '\n';
            break;
        
        case CLOSE_PARANTHESES:
            std::cout << "CLOSE_PARANTHESES\t" << t.lexemes << '\n';
            break;
        
        case ID:
            std::cout << "ID\t\t\t" << t.lexemes << '\n';
            break;
        
        case INTEGER:
            std::cout << "INTEGER\t\t\t" << t.lexemes << '\n';
            break;
        
        case REAL:
            std::cout << "REAL\t\t\t" << t.lexemes << '\n';
            break;
        
        case ERROR_SY:
            std::cout << "ERROR_SY\t\t" << t.lexemes << '\n';
            break;
        default:
            break;
        }
        t = get_tokens();
    }
    std::cout << "_EOF_\t\t\t" << t.lexemes << '\n';
}