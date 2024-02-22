#ifndef SCANNER_H_
#define SCANNER_H_

#include<iostream>
#include<fstream>
#include<string>

enum token{CIN, COUT, IN, OUT, MULTI, PLUS, OPEN_PARANTHESES, CLOSE_PARANTHESES, ID, INTEGER, ERROR, _EOF_};

struct token_t {
    token t;
    std::string value = "";
};

class scanner {
    private:
        std::ifstream f;

        token chech_reserved(const std::string&);
    public:
        scanner(const std::string&);

        ~scanner();

        token get_tokens();

        void display_tokens();
};

#endif