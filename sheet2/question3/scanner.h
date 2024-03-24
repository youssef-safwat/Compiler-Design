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
  q10,
  q6,
  q7,
  q8,
  q9,
  q11,
  q12,
  q13,
  q14,
  q15, // Final states
  dead_state
};

// Declare the set of tokens
enum tokens {
  rpran,
  lpran,
  multisym,
  plussym,
  ggsym,
  llsym,
  real,
  integer,
  cinsym,
  coutsym,
  identifier,
  ENDOFFILE,
  _ERROR_
};

struct token_t {
  tokens name;
  string value;
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
