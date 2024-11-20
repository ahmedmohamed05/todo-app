#pragma once
#include "./date.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

class Util {
public:
  enum randomType { smallLetter, capitalLetter, digit, specialCharacter, mix };

  static void urand() { srand(time(0)); }

  static int randomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
  }

  static char randomChar(const randomType &type) {
    char c;
    switch (type) {
    case randomType::smallLetter:
      c = randomNumber(97, 122);
      break;
    case randomType::capitalLetter:
      c = randomNumber(65, 90);
      break;
    case randomType::digit:
      c = randomNumber(48, 57);
      break;
    case randomType::specialCharacter:
      c = randomNumber(33, 47);
      break;
    case randomType::mix:
      c = randomChar(randomType(randomNumber(0, 3)));
      break;
    }
    return c;
  }

  static bool isSpecialCharacter(const char &c) {
    short test = c;
    return 33 <= c && c <= 47;
  }

  static std::string randomWord(const randomType &type, int wordLength,
                                bool withoutSpecialCahracters = true,
                                bool withoutDigits = false) {
    std::string word = "";
    for (int i = 1; i <= wordLength; i++) {
      char c = randomChar(type);

      // removing special characters
      if (withoutSpecialCahracters) {
        if (isSpecialCharacter(c)) {
          i -= 1;
          continue;
        }
      }

      // removing digits
      if (withoutDigits) {
        if (isdigit(c)) {
          i -= 1;
          continue;
        }
      }

      word += c;
    }
    return word;
  }

  // This method only return's key without special characters and number
  static std::string randomKey(short terms = 4, short termLength = 4,
                               bool useSmallLetters = false) {

    std::string key = "";

    for (short i = 1; i <= terms; i++) {
      std::string word = "";
      if (useSmallLetters) {
        word = randomWord(randomType::mix, termLength, true, true);
      } else {
        word = randomWord(randomType::capitalLetter, termLength, true, true);
      }

      key += word + '-';
    }

    // Removing last '-'
    key.pop_back();

    return key;
  }

  // This method only return's key without special characters and number
  static std::vector<std::string> randomKeys(int numberOfKeys, short terms = 4,
                                             short termLength = 4,
                                             bool useSmallLetters = false) {
    std::vector<std::string> keys = {};

    for (int i = 1; i <= numberOfKeys; i++) {
      keys.push_back(randomKey(terms, termLength, useSmallLetters));
    }
    return keys;
  }

  static void print(const std::vector<std::string> &v) {
    for (const std::string &str : v) {
      std::cout << str << '\n';
    }
  }
  static void print(const std::vector<int> &v) {
    for (int i : v) {
      std::cout << i << '\n';
    }
  }
  static void print(int arr[], int size) {
    for (int i = 0; i < size; i++) {
      std::cout << arr[i] << '\n';
    }
  }
  static void print(std::string arr[], int size) {
    for (int i = 0; i < size; i++) {
      std::cout << arr[i] << '\n';
    }
  }

  // *: Swap methods
  template <typename t> static void swap(t &a, t &b) {
    t c = a;
    a = b;
    b = c;
  }

  static std::string tabs(short tabs) {
    std::string str = "";

    for (short i = 1; i <= tabs; i++) {
      str += '\t';
    }

    return str;
  }

  // *: Filling vector with random things
  static void fillWithRandomints(std::vector<int> &v, int min, int max) {
    for (int &i : v) {
      i = randomNumber(min, max);
    }
  }
  static void fillWithRandomints(int arr[], int arrayLength, int min, int max) {
    for (int i = 0; i < arrayLength; i++) {
      arr[i] = randomNumber(min, max);
    }
  }

  static void fillWithRandomStrings(std::vector<std::string> &v,
                                    randomType type, int wordLength,
                                    bool withoutSpecialCahracters = true,
                                    bool withoutDigits = false) {
    for (std::string &str : v) {
      str =
          randomWord(type, wordLength, withoutSpecialCahracters, withoutDigits);
    }
  }

  static void fillWithRandomStrings(std::string arr[], int arrayLength,
                                    randomType type, int wordLength,
                                    bool withoutSpecialCahracters = true,
                                    bool withoutDigits = false) {
    for (int i = 0; i < arrayLength; i++) {
      arr[i] =
          randomWord(type, wordLength, withoutSpecialCahracters, withoutDigits);
    }
  }

  static void fillWithRandomKeys(std::vector<std::string> &v, short terms = 4,
                                 short termLength = 4,
                                 bool useSmallLetters = false) {
    v = randomKeys(v.size(), terms, termLength, useSmallLetters);
  }

  static void fillWithRandomKeys(std::string arr[], int arrayLength,
                                 short terms = 4, short termLength = 4,
                                 bool useSmallLetters = false) {
    for (int i = 0; i < arrayLength; i++) {
      arr[i] = randomKey(terms, termLength, useSmallLetters);
    }
  }

  static std::string encrypt(const std::string &str, short key) {
    std::string encryptedText = "";
    for (const char c : str) {
      encryptedText += c + key;
    }
    return encryptedText;
  }
  static std::string decrypt(const std::string &str, short key) {
    std::string decryptedText = "";
    for (const char c : str) {
      decryptedText += c - key;
    }
    return decryptedText;
  }

  static void shuffle(std::vector<int> &v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
      swap<int>(v[randomNumber(1, size) - 1], v[randomNumber(1, size) - 1]);
    }
  }
  static void shuffle(std::vector<std::string> &v) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
      swap<std::string>(v[randomNumber(1, size) - 1],
                        v[randomNumber(1, size) - 1]);
    }
  }
  static void shuffle(int arr[], int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
      swap<int>(arr[randomNumber(1, arrayLength) - 1],
                arr[randomNumber(1, arrayLength) - 1]);
    }
  }
  static void shuffle(std::string arr[], int arrayLength) {
    for (int i = 0; i < arrayLength; i++) {
      swap<std::string>(arr[randomNumber(1, arrayLength) - 1],
                        arr[randomNumber(1, arrayLength) - 1]);
    }
  }

  // TODO: Complete this function
  static std::string numberToTxet(int n) {
    if (n == 0)
      return "";

    // 1 to 9
    if (1 <= n && n <= 9) {
      std::string arr[9] = {"One", "Two",   "Three", "Four", "Five",
                            "Six", "Seven", "Eight", "Nine"};
      return arr[n - 1];
    }

    // 11 to 19
    if (11 <= n && n <= 19) {
      std::string arr[9] = {"Eleven",    "Twelve",   "Thirteen",
                            "Fourteen",  "Fifteen",  "Sixteen",
                            "Seventeen", "Eighteen", "Nineteen"};
      return arr[n - 11];
    }

    // 10, 20, 30 ... 90
    if (n <= 90 && n % 10 == 0) {
      std::string arr[10] = {"Ten",   "Twenty",  "Thirty", "Fourty", "Fifty",
                             "Sixty", "Seventy", "Eighty", "ninety"};
      return arr[n / 10];
    }

    if (n <= 900 && n % 100 == 0) {
      return numberToTxet(n / 100) + " Hundred";
    }
  }

  static std::string repeat(std::string str, unsigned times = 1) {
    std::string result = str;
    for (unsigned i = 1; i < times; i++) {
      result += str;
    }
    return result;
  }

  static std::string repeat(char c, unsigned times = 1) {
    return repeat(std::to_string(c), times);
  }
};
