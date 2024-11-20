#pragma once
#include <ctime>
#include <iostream>

class Header {
protected:
  static void printRow(int length, std::string character = "=") {
    for (int i = 1; i <= length; i++) {
      std::cout << character;
    }
    std::cout << '\n';
  }

  static std::string getTimeDate() {
    std::string result = "";

    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    result += now->tm_hour + ":";
    result += now->tm_min + ":";
    result += now->tm_sec;

    return result;
  }

public:
  static void header(std::string title, int rowLength) {
    printRow(rowLength);
    std::cout << title << '\n';
    printRow(rowLength);
  }
};