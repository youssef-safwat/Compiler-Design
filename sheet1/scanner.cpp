#include "scanner.h"

scanner::scanner(const std::string& s) {
    f.open(s);
    if(!f) {
        exit(1);
    }
}

scanner::~scanner() {
    f.close();
}

token scanner::chech_reserved(const std::string& s) {
    if(s == "cin") return CIN;
    else if(s == "cout") return COUT;
    return ID;
}

token scanner::get_tokens() {
    std::string s;
    char c;

    f.get(c);
    if(c == '+') return PLUS;
    else if(c == '*') return MULTI;
    else if(c == '(') return OPEN_PARANTHESES;
    else if(c == ')') return CLOSE_PARANTHESES;
    else if(c == '<') {
        f.get(c);
        if(c == '<') return OUT;
        else return ERROR;
    }
    else if(c == '>') {
        f.get(c);
        if(c == '>') return IN;
        else return ERROR; 
    }

    else if(isalpha(c)) {
        s = c;
        f.get(c);
        while(isalnum(c) && !f.eof()) {
            s += c;
            f.get(c);
        }
        f.putback(c);
        return chech_reserved(s);
    }

    else if(isdigit(c)) {
        s = c;
        f.get(c);
        while(isdigit(c) && !f.eof()) {
            s += c;
            f.get(c);
        }
        f.putback(c);
        return INTEGER;
    }

    return _EOF_;
}

void scanner::display_tokens() {
    token t = get_tokens();

    while(t != _EOF_) {
        switch (t)
        {
        case COUT:
            std::cout << "COUT\n";
            break;
        case CIN:
            std::cout << "CIN\n";
            break;
        case PLUS:
            std::cout << "+\n";
            break;
        case MULTI:
            std::cout << "*\n";
            break;
        case CLOSE_PARANTHESES:
            std::cout << "(\n";
            break;
        case OPEN_PARANTHESES:
            std::cout << "(\n";
            break;
        case IN:
            std::cout << ">>\n";
            break;
        case OUT:
            std::cout << "<<\n";
            break;
        case ID:
            std::cout << "ID\n";
            break;
        case INTEGER:
            std::cout << "INTEGER\n";
            break;
        case ERROR:
            std::cout << "ERROR\n";
            break;
        default:
            break;
        }
        t = get_tokens();
    }
    if(t == _EOF_) std::cout << "END OF FILE\n";
}