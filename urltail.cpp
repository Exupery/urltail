#include <iostream>

int main(int argc, char* argv[]) {

  if (argc == 1) {
    std::cout << "ERROR: no URL provided" << std::endl;

    return 1;
  }

  std::cout << "Tailing " << argv[1] << std::endl;

  return 0;
}