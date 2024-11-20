#pragma once
#include <iostream>
#include <vector>
using namespace std;

namespace mstring {

// Split String And Returns vector of strings
vector<string> splitString(string str, string delimiter = " ") {
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

// Print first letter from each word in string
void printLetters(string str) {
  for (string &word : mstring::splitString(str))
    cout << word[0] << '\n';
}

// Print each word in string
void printWords(string str) {
  for (string &word : mstring::splitString(str))
    cout << word << '\n';
}

// Capitalize each word in a string
string capitalize(string str) {
  bool isFirstLetter = true;
  for (char &letter : str) {
    if (letter != ' ' && isFirstLetter)
      letter = char(toupper(letter));
    isFirstLetter = (letter == ' ');
  }
  return str;
}

// Make frist letter of each word a small letter
string smallLetters(string str) {
  bool isFirstLetter = true;
  for (char &letter : str) {
    if (letter != ' ' && isFirstLetter)
      letter = char(tolower(letter));
    isFirstLetter = (letter == ' ');
  }
  return str;
}

// Convert the string to upper case
string toUpperCase(string str) {
  for (char &letter : str)
    letter = char(toupper(letter));
  return str;
}

// Convert the string to lower case
string toLowerCase(string str) {
  for (char &letter : str)
    letter = char(tolower(letter));
  return str;
}

// Invert string case
void invertString(string &str) {
  for (char &letter : str)
    letter = (islower(letter) ? toupper(letter) : tolower(letter));
}

// Count small letters in setring
unsigned short countSmallLetters(string str) {
  unsigned short counter = 0;

  for (char &letter : str)
    if (islower(letter))
      counter++;
  return counter;
}

// Count capital letters in setring
unsigned short countCapitalLetters(string str) {
  unsigned short counter = 0;

  for (char &letter : str)
    if (isupper(letter))
      counter++;
  return counter;
}

// Count a specific letter in string
unsigned short countLetter(string str, char letterToCount,
                           bool maching = true) {
  unsigned short counter = 0;

  if (!maching) {
    letterToCount = tolower(letterToCount);
    str = mstring::toLowerCase(str);
  }

  for (const char &letter : str) {
    if (letter == letterToCount)
      counter++;
  }

  return counter;
}

// Check if the input letter is a vowel
bool isVowel(char letter) {
  letter = tolower(letter);
  return (letter == 'a' || letter == 'i' || letter == 'o' || letter == 'e' ||
          letter == 'u');
}

// count vowels in given string
unsigned short countVowels(string str) {
  unsigned short counter = 0;

  for (const char &letter : str)
    if (mstring::isVowel(letter))
      counter++;

  return counter;
}

// Print all vowels in given string
void printStringVowels(string str) {
  for (const char &letter : str)
    if (isVowel(letter))
      cout << letter << " ";
  cout << "\n";
}

// Cut all the spaces on the left
void trimLeft(string &str) {
  for (short i = 0; i < str.length(); i++)
    if (str[i] != ' ') {
      str.erase(0, i);
      break;
    };
}

// Cut all the spaces on the right
void trimRight(string &str) {
  for (short i = str.length() - 1; i >= 0; i--)
    if (str[i] != ' ') {
      str.erase(i + 1, str.length() - 1);
      break;
    };
}

// Cut all the spaces in the string
void trim(string str) {
  mstring::trimRight(str);
  mstring::trimLeft(str);
}

// Join string from vector
string join(vector<string> vString, string sperator = " ") {
  string str = "";
  for (short i = 0; i < vString.size() - 1; i++)
    str += vString[i] + sperator;
  return str + vString[vString.size() - 1];
}

// Join string from array
string join(string aString[], unsigned length, string sperator = " ") {
  string str = "";
  for (short i = 0; i < length - 1; i++)
    str += aString[i] + sperator;
  return str + aString[length - 1];
}

// Reverse word in string start from end to begining
string reverseWordsInString(string str, string sperator = " ") {
  string reversedStr = "";
  vector<string> vString = splitString(str, sperator);
  for (short i = vString.size() - 1; i >= 0; i--)
    reversedStr += vString[i] + sperator;

  return reversedStr.substr(0, reversedStr.length() - sperator.length());
}

// Replace words in string
void replace(string &str, string wordToReplace, string newWord,
             bool maching = true) {
  if (!maching) {
    str = mstring::toLowerCase(str);
    wordToReplace = mstring::toLowerCase(wordToReplace);
  }

  short position;
  if ((position = str.find(wordToReplace)) != str.npos) {
    str.replace(position, wordToReplace.length(), newWord);
  } else {
    cerr << "Not Found\n";
    exit(EXIT_FAILURE);
  }
}

// Remove Punctuations Function
void removePunctuations(string &str) {
  for (short i = 0; i < str.length(); i++) {
    if (ispunct(str[i])) {
      str.erase(i, 1);
    }
  }
}

// Check if the string is a number
bool isNumber(string s) {
  for (const char &c : s) {
    if (!isdigit(c))
      return false;
  }
  return true;
}

} // namespace mstring
