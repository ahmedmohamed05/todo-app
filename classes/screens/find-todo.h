#pragma once
#include "../libs/input.h"
#include "../main/global.h"
#include "./header.h"
#include <iostream>

// TODO: change this to be submenu like list actions and it's screens

class FindTodoScreen : protected Header {
  enum _FindOption { byText, byId, backToMainMenu };

  static _FindOption _readFindOption() {
    cout << "[1]  Find Todo By Text." << endl;
    cout << "[2]  Find Todo By Id." << endl;
    cout << "[3]  Back to Main Menu." << endl;

    short input =
        Input::readShortInRange("Choice From 1 to 3: ", 1, 3,
                                "Please Choose From The Available Options.");
    return _FindOption(input - 1);
  }

  // Return -2 if the option is back to main menu
  static int _find(_FindOption option) {
    switch (option) {
    case byText: {
      std::string input = Input::readString("Enter Todo Text To Find: ");
      int i = list.find(input);
      while (i == -1) {
        std::cout << "Todo Not Found, Try Again\n";
        input = Input::readString("Enter Todo Text To Find: ");
        i = list.find(input);
      }
      return i;
    }
    case byId: {
      int id = Input::readInt("Enter Todo ID: ");
      int i = list.find(id);
      while (i == -1) {
        std::cout << "Todo Not Found, Try Again\n";
        id = Input::readInt("Enter Todo ID: ");
        i = list.find(id);
      }
      return i;
    }
    case backToMainMenu:
      return -2;
    }
    return -2;
  }

  static void _printTodo(Todo &todo) {
    std::cout << "--------------------------------------\n";
    std::cout << "Todo Information:\n";
    std::cout << "What To Do  : " << todo.getText() << '\n';
    std::cout << "Is Completed: " << todo.isCompleted() << '\n';
    std::cout << "Created At  : " << todo.getCreationDate() << '\n';
    std::cout << "DeadLine    : " << todo.getDeadLine() << '\n';
    std::cout << "ID          : " << todo.getId() << '\n';
    std::cout << "--------------------------------------\n";
  }

  enum _Actions {
    edit,
    check,
    uncheck,
    deleteTodo,
    setDeadline,
    removeDeadline,
    findAnotherTodo,
    cancel
  };

  static void _printActionsMenu() {
    std::cout << "[1]  Edit.\n";
    // TODO: i can make it dynamicly says check/uncheck a todo based on it's
    // status
    std::cout << "[2]  Check.\n";
    std::cout << "[3]  Uncheck.\n";
    std::cout << "[4]  Delete.\n";
    // TODO: change this too if there is a deadline already
    std::cout << "[5]  Set/Add DeadLine.\n";
    std::cout << "[6]  Remove Deadline.\n";
    std::cout << "[7]  Find Another Todo.\n";
    std::cout << "[8]  Cancel.\n";
  }

  static short _readAction() {
    short input =
        Input::readShortInRange("Choice From 1 To 8: ", 1, 8,
                                "Invalid Action Number, Please Try Again.");
    return input;
  }

  static void _performAction(Todo &todo, _Actions action) {
    switch (action) {
    case edit: {
      std::string newText = Input::readString("Enter New Todo Text: ");
      todo.setText(newText);
      list.saveUpdates();
      system("clear");
      std::cout << "Todo Text Updated Successfully.\n";
      break;
    }
    case check: {
      char input =
          Input::readCharacter("Do You Want to Check This Todo? (y/n): ");

      if (tolower(input) == 'y') {
        todo.check();
        list.saveUpdates();
        std::cout << "Todo Checked Successfully.\n";
        break;
      }
      std::cout << "Operation Cancelled.\n";
      break;
    }
    case uncheck: {
      char input =
          Input::readCharacter("Do You Want to Uncheck This Todo? (y/n): ");

      if (tolower(input) == 'y') {
        todo.unCheck();
        list.saveUpdates();
        std::cout << "Todo Unchecked Successfully.\n";
        break;
      }
      std::cout << "Operation Cancelled.\n";
      break;
    }
    case deleteTodo: {
      char input =
          Input::readCharacter("Do You Want to Delete This Todo? (y/n): ");

      if (tolower(input) == 'y') {
        todo.markAsDeleted();
        list.saveUpdates();
        std::cout << "Todo Deleted Successfully.\n";
        break;
      }

      std::cout << "Operation Cancelled.\n";
      break;
    }
    case setDeadline: {
      std::string deadline = Input::readString("Enter New Deadline: ");
      bool success = todo.setDeadLine(deadline);
      if (success) {
        std::cout << "deadline Set Successfully.\n";
      } else {
        std::cout << "Invalid Date Format, Please Try Again.\n";
      }
      break;
    }
    case removeDeadline: {
      char input = Input::readCharacter(
          "Do You Want to Remove Deadline from This Todo? (y/n): ");

      if (tolower(input) == 'y') {
        todo.removeDeadLine();
        std::cout << "Deadline Removed Successfully.\n";
        break;
      }
      std::cout << "Operation Cancelled.\n";
      break;
    }
    case findAnotherTodo: {
      system("clear");
      break;
    }
    case cancel: {
      return;
    }
    }
    list.saveUpdates();
    printScreen();
  }

public:
  static void printScreen() {
    Header::header("\t\tFind Todo", 60);

    if (list.isEmpty()) {
      cout << "\t\tYou Don't Have Any Todos.\n";
      return;
    }

    _FindOption option = _readFindOption();

    int i = _find(option);

    // Going Back To Main Menu
    if (i == -2) {
      system("clear");
      return;
    }

    // This Code wont execute as we already checked above for finding todos, JIC
    if (i == -1) {
      cerr << "Error: Todo Not Found.\n";
    }

    Todo *todo = &list.getAllTodos()->at(i);

    system("clear");
    _printTodo(*todo);
    _printActionsMenu();
    short action = _readAction();
    _performAction(*todo, _Actions(action - 1));
  }
};