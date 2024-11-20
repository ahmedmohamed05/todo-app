#include "../libs/date.h"
#include "../libs/mstring.h"
#include <iostream>

#pragma once

class Todo {
private:
  std::string _todoText, _creationDate, _deadLine;
  bool _markAsDeleted, _status;
  unsigned _id;
  static unsigned _firstId;

  // TODO: Change this to be within creation date
  // short _hour, _min, _sec;

public:
  // Send the deadline like in this format DD/MM/YYYY
  Todo(std::string whatToDo, std::string deadLine = "no deadline selected") {
    _todoText = whatToDo;

    {
      Date today;
      _creationDate = Date::convertDateToString(today);

      // TODO
      // std::time_t t = std::time(0);
      // std::tm *now = std::localtime(&t);
      // _hour = now->tm_hour;
      // _min = now->tm_min;
      // _sec = now->tm_sec;
    }

    if (deadLine != "no deadline selected" && !deadLine.empty()) {
      Date d(deadLine, "/");
      _deadLine = Date::convertDateToString(d);
    } else {
      _deadLine = deadLine;
    }

    _markAsDeleted = false;
    _status = false;
    _id = _firstId++;
  }

  std::string getText() { return _todoText; }
  void setText(std::string newText) { _todoText = newText; }

  unsigned getId() { return _id; }

  std::string getDeadLine() { return _deadLine; }

  // send the deadline in this format DD/MM/DDDD
  bool setDeadLine(std::string newDeadLine) {
    if (newDeadLine == "No DeadLine Selected") {
      _deadLine = _deadLine;
      return true;
    }

    for (char c : newDeadLine) {
      if (c == '/')
        continue;

      if (!isdigit(c))
        return false;
    }

    _deadLine = newDeadLine;
    return true;
  }

  std::string getCreationDate() { return _creationDate; }

  bool isMarkedAsDeleted() { return _markAsDeleted; }

  void markAsDeleted() { _markAsDeleted = true; }

  void unMarkAsDeleted() { _markAsDeleted = false; }

  bool isCompleted() { return _status; }

  void check() { _status = true; }

  void unCheck() { _status = false; }

  void setStatus(bool newStatus) { _status = newStatus; }

  bool hasDeadLine() { return _deadLine != "no deadline selected"; }

  std::string getRecord() {
    std::string result = "", separator = " | ";
    result += this->getText() + separator;
    result += std::to_string(this->isCompleted()) + separator;
    result += this->getCreationDate() + separator;
    result += this->getDeadLine() + separator;
    result += std::to_string(this->getId());
    return result;
  }

  void setFromRecord(std::string record) {
    std::vector<std::string> vRecord = Mstring::split(record, " | ");

    _todoText = vRecord.at(0);
    _status = stoi(vRecord.at(1));
    _creationDate = vRecord.at(2);
    _deadLine = vRecord.at(3);
    _id = stoi(vRecord.at(4));
  }

  // TODO
  // std::string getCreationTimeDate() {
  //   std::string timeDate = getCreationDate();
  //   timeDate += ":" + std::to_string(_hour);
  //   timeDate += ":" + std::to_string(_min);
  //   timeDate += ":" + std::to_string(_sec);
  //   return timeDate;
  // }

  void removeDeadLine() { _deadLine = "No DeadLine Selected"; }
};