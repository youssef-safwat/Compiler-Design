#ifndef SCANNER_H_
#define SCANNER_H_

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
using std::fstream, std::cout, std::string;

// Declare the set of states as a enum
enum states {
  q0,
  q1,
  q2,
  q3,
  q4,
  q5,
  q6,
  q7,
  q8,
  q9,
  q10,
  q11,
  q12,
  q13,
  q14,
  q15,
  q16,
  q17,
  q18,
  q19,
  q20,
  q21,
  q22,
  q23,
  dead_state
};

// Declare the set of tokens
enum tokens {
  numeral,
  identifier,
  weak_operation,
  strong_operation,
  relation_operation,
  reserved_word,
  rsqrbracket,
  lsqrbracket,
  rpare,
  lpare,
  assign,
  colon,
  separator,
  semi_column,
  end_of_file,
  _error_
};

struct token_t {
  tokens name;
  string lexem;
};

// Declare prototype of scanner class
class scanner {
  // private instance
  fstream f;

  // private method
  // check_reserved method
  token_t check_reserved(const string &);

  // Declare public instance
public:
  // constructor
  scanner(const string &);

  // Destructor
  ~scanner();

  // get_token method
  token_t get_token();

  // display_token method
  void display_token();

  // token_to_string method
  string token_to_string(tokens);
};

#endif // !SCANNER_H_
