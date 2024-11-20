#pragma once
#include "../../main/global.h"
#include "../../main/todo.h"
#include "../header.h"
#include <iomanip>
#include <iostream>

class ListCompletedTodosScreen : protected Header {

  static void _printHeader() {
    std::cout << setw(25) << left << "Todo";
    std::cout << " | " << setw(15) << left << "Create Date";
    std::cout << " | " << setw(20) << left << "Deadline";
    std::cout << " | " << setw(15) << left << "ID";
  }

  static void _printTodo(Todo &todo) {
    std::cout << setw(25) << left << todo.getText();
    std::cout << " | " << setw(15) << left << todo.getCreationDate();
    std::cout << " | " << setw(20) << left << todo.getDeadLine();
    std::cout << " | " << setw(15) << left << todo.getId();
    std::cout << '\n';
  }

public:
  static void printScreen() {
    std::vector<Todo> vTodos = list.getCompletedTodos();

    if (vTodos.size() <= 0) {
      Header::header("\t\tYou Have Not Completed Any Todo Yet...", 50);
      return;
    }

    std::string msg =
        "\t\tYou Have Completed " + std::to_string(vTodos.size()) + " Task(s)";

    Header::header(msg, 60);
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
