#include "scanner.h"

// Constructor to open the file
scanner::scanner(const std::string &s) {
  f.open(s);
  // Check if file not opened
  if (!f) {
    cout << "File is not opened\n";
    exit(1);
  }
}

//  distractor to close the file
scanner::~scanner() { f.close(); }

// Define check_reserved function
token_t scanner::check_reserved(const string &s) {
  if (s == "cin") {
    return {CIN_SY, "cin"};
  } else if (s == "cout") {
    return {COUT_SY, "cout"};
  }
  return {ID, s};
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
    t = {PLUS, "+"};
    break;
  case '*':
    t = {MULTI, "*"};
    break;
  case '/':
    t = {DIVISION_SY, "/"};
    break;
  case '^':
    t = {POWER_SY, "^"};
    break;
  case '(':
    t = {OPEN_PARANTHESES, "("};
    break;
  case ')':
    t = {CLOSE_PARANTHESES, ")"};
    break;
  case '<':
    t.lexemes += c;
    f.get(c);
    if (c == '<')
      t = {LL_SY, "<<"};
    else if (c == '=')
      t = {LE_SY, "<="};
    else if (c == '>')
      t = {NE_SY, "<>"};
    else {
      t = {L_SY, "<"};
      f.putback(c);
    }
    break;
  case '>':
    t.lexemes += c;
    f.get(c);
    if (c == '>')
      t = {GG_SY, ">>"};
    else if (c == '=')
      t = {GE_SY, ">="};
    else {
      t = {G_SY, ">"};
      f.putback(c);
    }
    break;
  case '=':
    t.lexemes += c;
    f.get(c);
    if (c == '=')
      t = {EE_SY, "=="};
    else {
      t = {E_SY, "="};
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
    } else if (isdigit(c)) {
      // Check the integer number
      t.lexemes = c;
      while (isdigit(f.peek())) {
        f.get(c);
        t.lexemes += c;
      }
      // Check the real number
      if (f.peek() != '.') {
        t._token = INTEGER;
      } else if (f.peek() == '.') {
        t.lexemes += '.';
        f.get(c);
        // D+. is an error
        if (!isdigit(f.peek())) {
          t._token = ERROR_SY;
        } else {
          while (isdigit(f.peek())) {
            f.get(c);
            t.lexemes += c;
          }
          t._token = REAL;
        }
      }
    }
    // .D+ is accepted as a real number
    else if (c == '.') {
      t.lexemes = c;
      if (isdigit(f.peek())) {
        while (isdigit(f.peek())) {
          f.get(c);
          t.lexemes += c;
        }
        t._token = REAL;
      } else {
        t._token = ERROR_SY;
      }
    } else if (f.eof())
      t = {_EOF_, "end of file"};
  }
  return t;
}

// define of display_tokens function
void scanner::display_tokens() {
  token_t t = get_tokens();
  cout << "Toekn\t\t\tLexemes\n";
  cout << "----------------------------------\n";
  do {
    t = get_tokens();
    cout << token_to_string(t._token) << t.lexemes << '\n';
  } while (t._token != _EOF_);
}

// Define token_to_string function
string scanner::token_to_string(token t) {
  switch (t) {
  case PLUS:
    return "PLUS\t\t\t";
    break;
  case MULTI:
    return "MULTI\t\t\t";
    break;
  case CIN_SY:
    return "CIN_SY\t\t\t";
    break;
  case COUT_SY:
    return "COUT_SY\t\t\t";
    break;
  case GG_SY:
    return "GG_SY\t\t\t";
    break;
  case LL_SY:
    return "LL_SY\t\t\t";
    break;
  case LE_SY:
    return "LE_SY\t\t\t";
    break;
  case L_SY:
    return "L_SY\t\t\t";
    break;
  case NE_SY:
    return "NE_SY\t\t\t";
    break;
  case G_SY:
    return "G_SY\t\t\t";
    break;
  case E_SY:
    return "E_SY\t\t\t";
    break;
  case EE_SY:
    return "EE_SY\t\t\t";
    break;
  case GE_SY:
    return "GE_SY\t\t\t";
    break;
  case OPEN_PARANTHESES:
    return "OPEN_PARANTHESES\t";
    break;
  case CLOSE_PARANTHESES:
    return "CLOSE_PARANTHESES\t";
    break;
  case ID:
    return "ID\t\t\t";
    break;
  case INTEGER:
    return "INTEGER\t\t\t";
    break;
  case REAL:
    return "REAL\t\t\t";
    break;
  case POWER_SY:
    return "POWER_SY\t\t";
    break;
  case DIVISION_SY:
    return "DIVISION_SY\t\t";
    break;
  case ERROR_SY:
    return "ERROR_SY\t\t";
    break;
  case _EOF_:
    return "end of file\t\t";
    break;
  }
  return "UNKNOWN_TOKEN";
}
