#include "scanner.h"
#include <cctype>
// Declare constractor of scanner class
scanner::scanner(const string &file_name) {
  f.open(file_name);
  if (!f) {
    cout << "File cannot open\n";
    exit(1);
  }
}

// Declare the destructor
scanner::~scanner() { f.close(); }

// Declare check_reserved function
token_t scanner::check_reserved(const string &token) {
  if (token == "cin")
    return {cinsym, "cin"};
  else if (token == "cout")
    return {coutsym, "cout"};
  else
    return {identifier, token};
}

// Declare get_token function
token_t scanner::get_token() {
  char c;
  string token;
  while (isspace(f.peek()) && !f.eof()) {
    f.get(c);
  }
  states current_state = q0;
  while (!f.eof()) {
    switch (current_state) {
    case q0:

      if (isalpha(f.peek())) {
        f.get(c);
        current_state = q1;
        token += c;
      } else if (isdigit(f.peek())) {
        f.get(c);
        current_state = q2;
        token += c;
      } else if (c == '<')
        current_state = q5;
      else if (c == '(')
        current_state = q7;
      else if (c == ')')
        current_state = q8;
      else if (c == '*')
        current_state = q9;
      else if (c == '+')
        current_state = q12;
      else if (c == '.') {
        
        }
      else
        current_state = dead_state;
      break;
    case q1:
      if(isalnum(f.peek())) {
        f.get(c);
        token += c;
        current_state = q1;
      } else {
          return check_reserved(token);
        }
    }
  }
}
