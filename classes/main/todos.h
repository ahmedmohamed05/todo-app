#pragma once
#include "../libs/util.h"
#include "./todo.h"
#include <fstream>
#include <iostream>
#include <vector>

class TodosList {
private:
  std::string _todosFileName;
  std::vector<Todo> _todos;

  void _updateDataFile() {
    fstream file(_todosFileName, ios::out);

    if (file.is_open()) {
      std::vector<Todo> newList;

      for (Todo &todo : _todos) {
        if (todo.isMarkedAsDeleted()) {
          continue;
        }
        file << todo.getRecord() << '\n';
        newList.push_back(todo);
      }

      _todos = newList;
      return;
    } else {
      cerr << "Error: Todos file not open\n";
      file.close();
      exit(EXIT_FAILURE);
    }
  }

  bool _isValidIndex(int index) {
    return !(index < 0 || index >= _todos.size());
  }

public:
  TodosList(std::string todosFile = "todos.txt") {
    _todosFileName = todosFile;
    fstream file(_todosFileName, ios::in);

    if (file.is_open()) {
      // return if the file is empty
      if (file.peek() == std::ifstream::traits_type::eof()) {
        file.close();
        return;
      }

      std::string line;
      while (getline(file, line)) {
        Todo todo("x");
        todo.setFromRecord(line);
        _todos.push_back(todo);
      }
    }
  }

  bool isEmpty() { return _todos.empty(); }

  int find(unsigned id) {
    for (int i = 0; i < _todos.size(); i++) {
      if (_todos.at(i).getId() == id) {
        return i;
      }
    }
    return -1;
  }

  int find(std::string text) {
    for (int i = 0; i < _todos.size(); i++) {
      if (_todos.at(i).getText() == text) {
        return i;
      }
    }
    return -1;
  }

  std::vector<Todo> *getAllTodos() { return &_todos; }

  std::vector<Todo> getCompletedTodos() {
    std::vector<Todo> completedTodos;
    for (Todo &todo : _todos) {
      if (todo.isCompleted()) {
        completedTodos.push_back(todo);
      }
    }
    return completedTodos;
  }

  std::vector<Todo> getUncompletedTodos() {
    std::vector<Todo> uncompletedTodos;
    for (Todo &todo : _todos) {
      if (!todo.isCompleted()) {
        uncompletedTodos.push_back(todo);
      }
    }
    return uncompletedTodos;
  }

  std::vector<Todo> getTodosWithDeadLine() {
    std::vector<Todo> deadLineTodos;

    for (Todo &todo : _todos) {
      if (todo.hasDeadLine()) {
        deadLineTodos.push_back(todo);
      }
    }

    return deadLineTodos;
  }

  std::vector<Todo> getTodosWithoutDeadline() {
    std::vector<Todo> todosWithoutDeadline;
    for (Todo &todo : _todos) {
      if (!todo.hasDeadLine()) {
        todosWithoutDeadline.push_back(todo);
      }
    }
    return todosWithoutDeadline;
  }

  int findTodo(std::string text) {
    for (int i = 0; i < _todos.size(); i++) {
      if (_todos[i].getText() == text)
        return i;
    }
    return -1;
  }

  bool deleteTodo(std::string text) {
    int index = findTodo(text);
    if (index == -1)
      return false;

    std::vector<Todo> newList;

    for (Todo &todo : _todos) {
      if (todo.getText() == text) {
        todo.markAsDeleted();
        _updateDataFile();
        return true;
      }
    }

    return false;
  }

  bool deleteTodo(int index) { return true; }

  // 1: success, 0: warning, -1: error
  short addTodo(std::string whatToDo, std::string deadLine = "") {
    short state = 1;

    int length = this->length();
    for (int i = 0; i < length; i++) {
      if (_todos[i].getText() == whatToDo) {
        state = 0;
        break;
      }
    }

    Todo t(whatToDo, deadLine);

    _todos.push_back(t);

    _updateDataFile();

    return state;
  }

  int length() { return _todos.size(); }

  void removeDuplicated() {
    int length = _todos.size();

    if (length < 1)
      return;

    for (int i = 0; i < length; i++) {
      bool found = false;
      // Check if the todo exist
      for (int j = i + 1; j < length; j++) {
        if (_todos[i].getText() == _todos[j].getText()) {
          _todos[j].markAsDeleted();
          break;
        }
      }
    }

    _updateDataFile();
  }

  void removeCompleted() {
    for (Todo &todo : _todos) {
      if (todo.isCompleted()) {
        todo.markAsDeleted();
      }
    }
    _updateDataFile();
  }

  void removeExpiredTodos() {
    for (Todo &todo : _todos) {
      if (todo.hasDeadLine()) {
        Date deadLine(todo.getDeadLine());
        Date today;

        if (Date::isDate1AfterDate2(today, deadLine)) {
          todo.markAsDeleted();
        }
      }
    }

    _updateDataFile();
  }

  int todosLeft() {
    int counter = 0;
    for (Todo &todo : _todos) {
      if (!todo.isCompleted())
        counter++;
    }

    return counter;
  }

  bool checkTodoAt(int position) {
    if (!_isValidIndex(position - 1)) {
      return false;
    }

    _todos.at(position - 1).check();
  }

  bool uncheckTodoAt(int position) {
    if (!_isValidIndex(position - 1)) {
      return false;
    }

    _todos.at(position - 1).unCheck();
  }

  bool editTodoAt(int position, std::string whatToDo) {
    if (!_isValidIndex(position - 1)) {
      return false;
    }

    _todos.at(position - 1).setText(whatToDo);
  }

  bool removeDeadLineFromTodoAt(int position) {

    if (!_isValidIndex(position - 1)) {
      return false;
    }

    _todos.at(position - 1).removeDeadLine();
    _updateDataFile();
    return true;
  }

  void removeAllTodos() {
    _todos.clear();
    _updateDataFile();
  }

  void saveUpdates() { _updateDataFile(); }
};
