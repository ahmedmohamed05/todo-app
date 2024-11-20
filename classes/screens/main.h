#pragma once
#include <iostream>

#include "../libs/input.h"
#include "../main/todos.h"
// Screens
#include "./find-todo.h"
#include "./header.h"
#include "./list-actions-screens/list-actions.h"
#include "./new-todo.h"
#include "./remove-actions.h"

class MainScreen : protected Header {
private:
  enum _MainOptions { listActions, findTodo, addNew, removeActions, exitApp };

  static _MainOptions _readOption() {
    short option = Input::readShortInRange("Choice From 1 to 5: ", 1, 5);
    return _MainOptions(option - 1);
  }

  static void _performAction(_MainOptions action) {
    system("clear");
    switch (action) {
    case listActions:
      ListActionsScreen::printScreen();
      break;
    case findTodo:
      FindTodoScreen::printScreen();
      break;
    case addNew:
      AddNewTodoScreen::printScreen();
      break;
    case removeActions:
      RemoveActionsScreen::printScreen();
      break;
    case exitApp:
      std::cout << "Good By :-)\n";
      exit(EXIT_SUCCESS);
      return;
    }
    printScreen();
  }

public:
  static void printScreen() {
    Header::header("\t\t\tMain Screen", 60);

    std::cout << "[1]  List Actions Submenu.\n";
    std::cout << "[2]  Find Todo by Text/ID.\n";
    std::cout << "[3]  Add New Todo.\n";
    std::cout << "[4]  Remove Actions Submenu.\n";
    std::cout << "[5]  Exit.\n";
    std::cout << "===========================================\n";

    _MainOptions option = _readOption();
    _performAction((option));
  }
};