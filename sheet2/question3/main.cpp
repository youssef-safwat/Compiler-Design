#include "scanner.h"

int main(int argc, char *argv[]) {
  scanner s("myCode.txt");
  // Display the token
  s.display_token();
  return 0;
}
