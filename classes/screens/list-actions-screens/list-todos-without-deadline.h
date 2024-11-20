#pragma once
#include "../../main/global.h"
#include "../../main/todo.h"
#include "../header.h"
#include <iomanip>
#include <iostream>

class ListTodosWithoutDeadLineScreen : protected Header {
  static void _printHeader() {
    std::cout << setw(25) << left << "Todo";
    std::cout << " | " << setw(20) << left << "Is Completed";
    std::cout << " | " << setw(25) << left << "Create Date";
    std::cout << " | " << setw(15) << left << "Deadline";
    std::cout << " | " << setw(15) << left << "ID";
  }

  static void _printTodo(Todo &todo) {
    std::cout << setw(25) << left << todo.getText();
    std::cout << " | " << setw(20) << left << todo.isCompleted();
    std::cout << " | " << setw(25) << left << todo.getCreationDate();
    std::cout << " | " << setw(15) << left << todo.getDeadLine();
    std::cout << " | " << setw(15) << left << todo.getId();
    std::cout << '\n';
  }

public:
  static void printScreen() {
    std::vector<Todo> vTodos = list.getTodosWithoutDeadline();
    if (vTodos.size() <= 0) {
      Header::header("\t\tYou Have Nothing To Todo", 50);
      return;
    }

    Header::header("\t\tList All Todos", 50);
    _printHeader();

    std::cout << '\n';
    std::cout << "--------------------------------------------------";
    std::cout << "--------------------------------------------------";
    std::cout << "----------------------\n";

    for (Todo &todo : vTodos) {
      _printTodo(todo);
    }
  }
};
