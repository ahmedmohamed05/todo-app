#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Mstring {
private:
  string _value;

public:
  Mstring() { this->_value = ""; }
  Mstring(string value) { this->_value = value; };

  string getValue() { return _value; }
  void setValue(string value) { this->_value = value; }

  void print() { cout << _value << endl; }

  void clear() { this->_value = ""; }

  // Split String And Returns vector of strings
  static vector<string> split(string str, const string &delimiter) {
    vector<string> vString;
    short delimPosition;

    while ((delimPosition = str.find(delimiter)) != str.npos) {
      vString.push_back(str.substr(0, delimPosition));
      str.erase(0, delimPosition + delimiter.length());
    }

    // Pushing last word in string
    if (str != "")
      vString.push_back(str);
    return vString;
  }
  vector<string> split(const string &delimiter) {
    return split(_value, delimiter);
  }

  // Print first letter from each word in string
  static void printFirstLetters(const string &str) {
    for (const string &word : split(str, " ")) {
      cout << word[0] << '\n';
    }
  }
  void printFirstLetters() { printFirstLetters(_value); }

  // Print each word in string
  static void printWords(string str, const string &delimiter) {
    for (string &word : split(str, delimiter)) {
      cout << word << '\n';
    }
  }
  void printWords(const string &delimiter) { printWords(_value, delimiter); }

  static void capitalize(string &str) {
    bool isFirstLetter = true;
    for (char &letter : str) {
      if (letter != ' ' && isFirstLetter) {
        letter = char(toupper(letter));
      }
      isFirstLetter = (letter == ' ');
    }
  }
  void capitalize() { capitalize(_value); }

  // Make frist letter of each word a small letter
  static void smallLetters(string &str) {
    bool isFirstLetter = true;
    for (char &letter : str) {
      if (letter != ' ' && isFirstLetter)
        letter = char(tolower(letter));
      isFirstLetter = (letter == ' ');
    }
  }
  void smallLetters() { smallLetters(_value); }

  // Convert the string to upper case
  static void toUpperCase(string &str) {
    for (char &letter : str) {
      letter = char(toupper(letter));
    }
  }
  void toUpperCase() { toUpperCase(_value); }

  // Convert the string to upper case
  static void toLowerCase(string &str) {
    for (char &letter : str) {
      letter = char(tolower(letter));
    }
  }
  void toLowerCase() { toLowerCase(_value); }

  // Invert string case
  static void invertCase(string &str) {
    for (char &letter : str) {
      letter = (islower(letter) ? toupper(letter) : tolower(letter));
    }
  }
  void invertCase() { invertCase(_value); }

  // Count small letters in setring
  static unsigned countSmallLetters(const string &str) {
    unsigned counter = 0;
    for (char letter : str) {
      if (islower(letter)) {
        counter++;
      }
    }
    return counter;
  }
  unsigned countSmallLetters() { return countSmallLetters(_value); }

  // Count Capital letters in setring
  static unsigned countCapitalLetters(const string &str) {
    unsigned counter = 0;
    for (char letter : str) {
      if (isupper(letter)) {
        counter++;
      }
    }
    return counter;
  }
  unsigned countCapitalLetters() { return countCapitalLetters(_value); }

  // Count a specific letter in string
  static unsigned countSpecificLetter(string str, char letterToCount,
                                      const bool matchingCase = true) {
    unsigned counter = 0;

    if (!matchingCase) {
      // Convert everything to lowercase
      letterToCount = tolower(letterToCount);
      Mstring::toLowerCase(str);
    }

    for (const char &letter : str) {
      if (letter == letterToCount)
        counter++;
    }

    return counter;
  }

  unsigned countSpecificLetter(char letterToCount,
                               const bool matchingCase = true) {
    return countSpecificLetter(_value, letterToCount, matchingCase);
  }

  // Check if the input letter is a vowel
  static bool isVowel(char letter) {
    letter = tolower(letter);
    return (letter == 'a' || letter == 'i' || letter == 'o' || letter == 'e' ||
            letter == 'u');
  }

  // count vowels in given string
  static unsigned countVowels(string str) {
    unsigned counter = 0;

    for (const char &letter : str) {
      if (isVowel(letter)) {
        counter++;
      }
    }

    return counter;
  }

  unsigned countVowels() { return countVowels(_value); }

  // Print all vowels in given string
  static void printVowels(string str) {
    for (const char &letter : str) {
      if (isVowel(letter)) {
        cout << letter << " ";
      }
    }
    cout << "\n";
  }
  void printVowels() { printVowels(_value); }

  // Cut all the spaces on the left
  static void trimLeft(string &str) {
    for (short i = 0; i < str.length(); i++) {
      if (str[i] != ' ') {
        str.erase(0, i);
        break;
      };
    }
  }
  void trimLeft() { trimLeft(_value); }

  // Cut all the spaces on the Right
  static void trimRight(string &str) {
    for (short i = str.length() - 1; i >= 0; i--) {
      if (str[i] != ' ') {
        str.erase(i + 1, str.length());
        break;
      };
    }
  }
  void trimRight() { trimRight(_value); }

  // Cut all the spaces in the string
  static void trim(string &str) {
    trimRight(str);
    trimLeft(str);
  }
  void trim() { trim(_value); }

  // Join string from vector
  static string join(const vector<string> &vString,
                     const string &sperator = " ") {
    string str = "";
    int size = vString.size();
    for (short i = 0; i < size - 1; i++)
      str += vString[i] + sperator;
    return str + vString[size - 1];
  }

  // Join string from array
  static string join(const string aString[], const unsigned length,
                     const string &sperator) {
    string str = "";
    for (short i = 0; i < length - 1; i++)
      str += aString[i] + sperator;
    return str + aString[length - 1];
  }

  // Setting the value from the given vector
  void from(const vector<string> &vString, const string &sperator = " ") {
    _value = join(vString, sperator);
  }

  // Setting the value from the given array
  void from(const string aString[], const unsigned length,
            const string &sperator) {
    _value = join(aString, length, sperator);
  }

  // Reverse word in string start from end to begining
  static string reverse(const string &str, const string &sperator) {
    string reversedStr = "";
    vector<string> vString = split(str, sperator);
    for (short i = vString.size() - 1; i >= 0; i--) {
      reversedStr += vString[i] + sperator;
    }

    // Removing last sperator added in the begining
    return reversedStr.substr(0, reversedStr.length() - sperator.length());
  }

  void reverse(const string &seprator) { _value = reverse(_value, seprator); }

  // Replace words in string
  static void replace(string &str, string wordToReplace, string newWord,
                      bool machingCase) {

    // Convert everything to lowercase
    if (!machingCase) {
      toLowerCase(str);
      toLowerCase(wordToReplace);
    }

    short position;
    if ((position = str.find(wordToReplace)) != str.npos) {
      str.replace(position, wordToReplace.length(), newWord);
    }
  }

  void replace(const string &wordToReplace, const string &newWord,
               bool machingCase) {
    replace(_value, wordToReplace, newWord, machingCase);
  }

  // Remove Punctuations Function
  static void removePunctuations(string &str) {
    for (short i = 0; i < str.length(); i++) {
      if (ispunct(str[i])) {
        str.erase(i, 1);
      }
    }
  }
  void removePunctuations() { removePunctuations(_value); }

  // Check if the string is a number
  static bool isNumber(string s) {
    for (const char &c : s) {
      if (!isdigit(c)) {
        return false;
      }
    }
    return true;
  }
  bool isNumber() { return isNumber(_value); }

  int length() { return _value.length(); }
};
