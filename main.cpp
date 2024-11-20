#include "./classes/screens/main.h"
#include <iostream>

int main() {
  while (1) {
    system("clear");
    MainScreen::printScreen();
  }

  return 0;
}

// TODO:  encryption will depend on the id but i need to re-read it from the
// file
