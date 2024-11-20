#pragma once
#include "../libs/input.h"
#include "../main/global.h"
#include "../main/todo.h"
#include "./header.h"
#include <iostream>

class AddNewTodoScreen : protected Header {

public:
  static void printScreen() {
    Header::header("\t\tAdd New Todo Screen", 60);

    char addAnotherTodo = 'y';
    while (tolower(addAnotherTodo) == 'y') {
      std::string todoText = Input::readString("Enter Todo Text: ");

      Todo todo(todoText);

      char addDeadLine = Input::readCharacter("Add Deadline? (y/n): ");

      if (tolower(addDeadLine) == 'y') {
        std::string deadline =
            Input::readString("Enter Deadline (dd/mm/yyyy): ");
        todo.setDeadLine(deadline);
      }

      short msg = list.addTodo(todo.getText(), todo.getDeadLine());

      if (msg == 1) {
        std::cout << "Todo Added Successfully.\n";
      } else if (msg == 0) {
        std::cout << "Warning: Todo Already Exists.\n";
      } else {
        std::cout << "Error: Failed to Add Todo.\n";
      }

      addAnotherTodo =
          Input::readCharacter("Do You Want To Add Another Todo? (y/n): ");
    }
  }
};