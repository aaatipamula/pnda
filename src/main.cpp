#include <iostream>
#include <fstream>

// NOTE: Incomplete file, need to add more framework for interpreter

int main(int argc, char *argv[]) {
  if (argc > 1) {
    std::cout << "Only one file accepted.";
  } else if (argc == 1) {
    std::ifstream InFile(argv[0]);
    execFile(InFile);
  } else {
    execPrompt();
  }
}
