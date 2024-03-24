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
      f.get(c);
      if (isalpha(c)) {
        current_state = q1;
        token += c;
      } else if (isdigit(c)) {
        current_state = q2;
        token += c;
      } else if (c == '<') {
        token += c;
        current_state = q5;
      } else if (c == '>') {
        token += c;
        current_state = q10;
      } else if (c == '(')
        current_state = q7;
      else if (c == ')')
        current_state = q8;
      else if (c == '*')
        current_state = q9;
      else if (c == '+')
        current_state = q12;
      else if (c == '.') {
        token += c;
        current_state = q3;
      } else {
        token += c;
        current_state = dead_state;
      }
      break;
    case q1:
      if (isalnum(f.peek())) {
        f.get(c);
        token += c;
        current_state = q1;
      } else {
        current_state = q13;
      }
      break;
    case q2:
      if (isdigit(f.peek())) {
        f.get(c);
        token += c;
        current_state = q2;
      } else if (f.peek() == '.') {
        f.get(c);
        token += c;
        current_state = q3;
      } else {
        current_state = q14;
      }
      break;
    case q3:
      f.get(c);
      if (isdigit(c)) {
        token += c;
        current_state = q4;
      } else {
        token += c;
        current_state = dead_state;
      }
      break;
    case q4:
      if (isdigit(f.peek())) {
        f.get(c);
        token += c;
        current_state = q4;
      } else {
        current_state = q15;
      }
      break;
    case q5:
      f.get(c);
      if (c == '<') {
        current_state = q6;
      } else {
        token += c;
        current_state = dead_state;
      }
      break;
    case q6:
      return {llsym, "<<"};
      break;
    case q7:
      return {lpran, "("};
      break;
    case q8:
      return {rpran, ")"};
      break;
    case q9:
      return {multisym, "*"};
      break;
    case q10:
      f.get(c);
      if (c == '>')
        current_state = q11;
      else {
        token += c;
        current_state = dead_state;
      }
      break;
    case q11:
      return {ggsym, ">>"};
      break;
    case q12:
      return {plussym, "+"};
      break;
    case q13:
      return check_reserved(token);
      break;
    case q14:
      return {integer, token};
      break;
    case q15:
      return {real, token};
      break;
    case dead_state:
      return {_ERROR_, token};
      break;
    default:
      break;
    }
  }
  return {ENDOFFILE, "End of file"};
}

// Declare display_token function
void scanner::display_token() {
  token_t t;
  cout << "Tokens\t\t\tLexems\n--------------------------------\n";
  do {
    t = get_token();
    cout << token_to_string(t.name) << "\t\t" << t.value << '\n';
  } while (t.name != ENDOFFILE);
}

// Declare token_to_string function
string scanner::token_to_string(tokens t) {
  switch (t) {
  case rpran:
    return "rpran_sym";
    break;
  case lpran:
    return "lpran_sym";
    break;
  case multisym:
    return "muli_tsym";
    break;
  case plussym:
    return "plus_sym";
    break;
  case ggsym:
    return "output_sym";
    break;
  case llsym:
    return "input_sym";
    break;
  case real:
    return "real_number";
    break;
  case integer:
    return "int_number";
    break;
  case cinsym:
    return "cin__sym";
    break;
  case coutsym:
    return "cout_sym";
    break;
  case identifier:
    return "identifier";
    break;
  case _ERROR_:
    return "syntax_error";
  default:
    break;
  }
  return "end_of_file";
}
