#pragma once
#include "../../libs/input.h"
#include "../header.h"
#include <iostream>

// Screens
#include "./list-all-todos.h"
#include "./list-completed-todos.h"
#include "./list-deadline-todos.h"
#include "./list-todos-without-deadline.h"
#include "./list-uncompleted-todos.h"

class ListActionsScreen : protected Header {
private:
  enum _ListActions {
    listAllTodos,
    listAllTodosWithDeadlines,
    listAllTodosWithoutDeadlines,
    listCheckedTodos,
    listUncheckedTodos,
    backToMainMenu
  };

  static void _performAction(_ListActions action) {
    system("clear");
    switch (action) {
    case listAllTodos:
      ListAllTodosScreen::printScreen();
      break;
    case listAllTodosWithDeadlines:
      ListTodosWithDeadLineScreen::printScreen();
      break;
    case listAllTodosWithoutDeadlines:
      ListTodosWithoutDeadLineScreen::printScreen();
      break;
    case listCheckedTodos:
      ListCompletedTodosScreen::printScreen();
      break;
    case listUncheckedTodos:
      ListUncompletedTodosScreen::printScreen();
      break;
    case backToMainMenu:
      return;
    }
    printScreen();
  }

public:
  static void printScreen() {
    Header::header("\t\tList Todos Submenu Screen", 60);

    std::cout << "[1]  List All Todos.\n";
    std::cout << "[2]  List All Todos with Deadlines.\n";
    std::cout << "[3]  List All Todos without Deadlines.\n";
    std::cout << "[4]  List Checked Todos.\n";
    std::cout << "[5]  List Unchecked Todos.\n";
    std::cout << "[6]  Back to Main Menu.\n";
    std::cout << "===========================================\n";

    short option = Input::readShortInRange("Choice From 1 to 6: ", 1, 6);
    _performAction(_ListActions(option - 1));
  }
};