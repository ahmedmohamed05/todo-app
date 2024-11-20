#pragma once
#include "../libs/input.h"
#include "./header.h"
#include <iostream>

class RemoveActionsScreen : protected Header {
private:
  enum _RemoveActions {
    removeAllTodos,
    removeExpiredTodos,
    removeDuplicated,
    backToMainMenu
  };

  static _RemoveActions _readAction() {
    short input = Input::readShortInRange("Choice From 1 to 4: ", 1, 4);
    return _RemoveActions(input - 1);
  }

  static void _performAction(_RemoveActions action) {
    // system("clear");
    switch (action) {
    case removeAllTodos: {
      char input =
          Input::readCharacter("Do You Want to Remove All Todos? (y/n): ");
      if (tolower(input) == 'y') {
        list.removeAllTodos();
        std::cout << "All Todos Removed Successfully.\n";
      } else {
        std::cout << "Operation Cancelled.\n";
      }
      break;
    }
    case removeExpiredTodos: {
      char input =
          Input::readCharacter("Do You Want to Expired Todos? (y/n): ");
      if (tolower(input) == 'y') {
        list.removeExpiredTodos();
        std::cout << "Expired Todos Removed Successfully.\n";
      } else {
        std::cout << "Operation Cancelled.\n";
      }
      break;
    }
    case removeDuplicated: {
      char input = Input::readCharacter(
          "Do You Want to Remove Duplicated Todos? (y/n): ");
      if (tolower(input) == 'y') {
        list.removeDuplicated();
        std::cout << "Duplicated Todos Removed Successfully.\n";
      } else {
        std::cout << "Operation Cancelled.\n";
      }
      break;
    }
    case backToMainMenu: {
      return;
    }
    }
    printScreen();
  }

public:
  static void printScreen() {
    Header::header("\t\tRemove Todos Submenu Screen", 60);

    if (list.isEmpty()) {
      std::cout << "\t\tYou Don't Have Any Todos.\n";
      return;
    }

    std::cout << "[1]  Remove All Todos.\n";
    std::cout << "[2]  Remove Expired Todos.\n";
    std::cout << "[3]  Remove Duplicated Todos.\n";
    std::cout << "[4]  Back to Main Menu.\n";
    std::cout << "===========================================\n";

    _RemoveActions option = _readAction();
    _performAction(option);
  }
};