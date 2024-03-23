#ifndef SCANNER_H_
#define SCANNER_H_

#include<iostream>
#include<fstream>
#include<string>
using std::cout, std::string;
enum token{DIVISION_SY, POWER_SY, G_SY, L_SY, GE_SY, LE_SY, E_SY, EE_SY, NE_SY, CIN_SY, COUT_SY, GG_SY, LL_SY, MULTI, PLUS, OPEN_PARANTHESES, CLOSE_PARANTHESES, ID, INTEGER, ERROR_SY, _EOF_, REAL};

//A lexeme is a sequence of characters in the source program that matches the pattern for a token and is identified by the lexical analyzer as an instance of that token.

struct token_t {
    token _token;
    string lexemes = "";
};

class scanner {
    private:
        // The file that i read from
        std::ifstream f;

        // Check_reserved function
        // Accept one string parameter as a lexemes
        // Return the token
        token_t check_reserved(const string&);
    public:
        // Constructor to check that the file is opened
        scanner(const string&);

        // distractor to close the file
        ~scanner();

        // get_tokens function
        // Accept no paramter
        // return each token in input file
        token_t get_tokens();

        // display_tokens function
        // Accept no paramter
        // Display each token and lexemes
        void display_tokens();

        // Token_to_string function
        // Accept token
        // Return string descrip this token
        std::string token_to_string(token);
};

#endif
