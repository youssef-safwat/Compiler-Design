#include "scanner.h"
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
  if (token == "true")
    return {reserved_word, "true"};
  else if (token == "false")
    return {reserved_word, "false"};
  else if (token == "and")
    return {reserved_word, "and"};
  else if (token == "or")
    return {reserved_word, "or"};
  else if (token == "read")
    return {reserved_word, "read"};
  else if (token == "write")
    return {reserved_word, "write"};
  else if (token == "if")
    return {reserved_word, "if"};
  else if (token == "then")
    return {reserved_word, "then"};
  else if (token == "endif")
    return {reserved_word, "endif"};
  else if (token == "while")
    return {reserved_word, "while"};
  else if (token == "do")
    return {reserved_word, "do"};
  else if (token == "end")
    return {reserved_word, "end"};
  else if (token == "begin")
    return {reserved_word, "begin"};
  else if (token == "program")
    return {reserved_word, "program"};
  else if (token == "is")
    return {reserved_word, "is"};
  else if (token == "var")
    return {reserved_word, "var"};
  else if (token == "integer")
    return {reserved_word, "integer"};
  else if (token == "boolean")
    return {reserved_word, "boolean"};
  else if (token == "not")
    return {reserved_word, "not"};
  else if (token == "skip")
    return {reserved_word, "skip"};
  else
    return {identifier, token};
}
// Declare get_token function
token_t scanner::get_token() {
  string token;
  char c;
  states current_state = q0;
  while (isspace(f.peek()) && !f.eof()) {
    f.get(c);
  }
  while (!f.eof()) {
    switch (current_state) {
    case q0:
      f.get(c);
      token += c;
      if (isdigit(c)) {
        current_state = q1;
      } else if (isalpha(c)) {
        current_state = q3;
      } else if (c == '+' || c == '*') {
        current_state = q5;
      } else if (c == '*' || c == '/') {
        current_state = q6;
      } else if (c == '<') {
        current_state = q7;
      } else if (c == '>') {
        current_state = q11;
      } else if (c == '=') {
        current_state = q14;
      } else if (c == ';') {
        current_state = q15;
      } else if (c == ',') {
        current_state = q16;
      } else if (c == '(') {
        current_state = q17;
      } else if (c == ')') {
        current_state = q18;
      } else if (c == ':') {
        current_state = q19;
      } else if (c == ']') {
        current_state = q22;
      } else if (c == '[') {
        current_state = q23;
      } else {
        current_state = dead_state;
      }
      break;
    case q1:
      f.get(c);
      if (isdigit(c)) {
        token += c;
        current_state = q1;
      } else {
        f.putback(c);
        current_state = q2;
      }
      break;
    case q2:
      return {numeral, token};
      break;
    case q3:
      f.get(c);
      if (isalnum(c)) {
        token += c;
        current_state = q3;
      } else {
        f.putback(c);
        current_state = q4;
      }
      break;
    case q4:
      return check_reserved(token);
      break;
    case q5:
      return {weak_operation, token};
      break;
    case q6:
      return {strong_operation, token};
      break;
    case q7:
      f.get(c);
      if (c == '>') {
        token += c;
        current_state = q8;
      } else if (c == '=') {
        token += c;
        current_state = q9;
      } else {
        f.putback(c);
        current_state = q10;
      }
      break;
    case q8:
    case q9:
    case q10:
      return {relation_operation, token};
      break;
    case q11:
      f.get(c);
      if (c == '=') {
        token += c;
        current_state = q12;
      } else {
        f.putback(c);
        current_state = q13;
      }
      break;
    case q12:
    case q13:
    case q14:
      return {relation_operation, token};
      break;
    case q15:
      return {semi_column, token};
      break;
    case q16:
      return {separator, token};
      break;
    case q17:
      return {lpare, token};
      break;
    case q18:
      return {rpare, token};
      break;
    case q19:
      f.get(c);
      if (c == '=') {
        token += c;
        current_state = q20;
      } else {
        f.putback(c);
        current_state = q21;
      }
      break;
    case q20:
      return {assign, token};
    case q21:
      return {colon, token};
    case q22:
      return {rsqrbracket, token};
    case q23:
      return {lsqrbracket, token};
    case dead_state:
      return {_error_, token};
      break;
    }
  }
  return {end_of_file, "end_of_file"};
}

// Declare display_token function
void scanner::display_token() {
  token_t t;
  cout << "Tokens\t\t\tLexems\n--------------------------------\n";
  do {
    t = get_token();
    cout << token_to_string(t.name) << "\t\t" << t.lexem << '\n';
  } while (t.name != end_of_file);
}

// Declare token_to_string function
string scanner::token_to_string(tokens t) {
  switch (t) {
  case numeral:
    return "numeral_value";
    break;
  case identifier:
    return "identifier";
    break;
  case weak_operation:
    return "weak_operation";
    break;
  case strong_operation:
    return "strong_operation";
    break;
  case relation_operation:
    return "relation_";
    break;
  case reserved_word:
    return "reserved_word";
    break;
  case rpare:
    return "right_paren";
    break;
  case lpare:
    return "left_paren";
    break;
  case assign:
    return "assigning";
    break;
  case colon:
    return "__colon__";
    break;
  case separator:
    return "separator";
    break;
  case semi_column:
    return "semi_column";
    break;
  case end_of_file:
    return "end_of_file";
    break;
  case rsqrbracket:
    return "rsqrbracket";
    break;
  case lsqrbracket:
    return "lsqrbracket";
    break;
  default:
    break;
  }
  return "Syntex_Error";
}
