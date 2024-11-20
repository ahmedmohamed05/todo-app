#pragma once
#include "./cstring.h"
#pragma once
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Date {
private:
  int _year, _month, _day;
  std::string _dayName, _monthName;
  std::string _separator;

protected:
  void setDay(const int &day, const int &month, const int &year) {
    if (!isValidDay(day, month, year)) {
      _day = 1;
    } else {
      _day = day;
    }
    _dayName = getDaysArray().at(getDayOrderInWeek(day, month, year));
  }

public:
  Date() { setToday(); }

  Date(std::string date, std::string separator = "/") {
    setDate(date, separator);
  }

  Date(int day, int month, int year, std::string separator = "/") {
    setDate(day, month, year, separator);
  }

  Date(int numberOfDays, int year, std::string separator = "/") {
    std::string date = getDateFromNumberOfDays(numberOfDays, year);
    setDate(date, separator);
  };

  void setDay(const int &day) {
    setDay(day, this->getMonth(), this->getYear());
  }

  // Get day properties
  int getDay() { return _day; }
  short getDayIndex() { return _day - 1; }
  std::string getDayName() {
    return getDayName(this->getDay(), this->getMonth(), this->getYear());
  }
  short getDayOrderInWeek() {
    return getDayOrderInWeek(this->getDay(), this->getMonth(), this->getYear());
  }

  // Get month properties
  void setMonth(int month) {
    if (!isValidMonth(month)) {
      _month = 1;
    } else {
      _month = month;
    }
    _monthName = getMonthName(month);
  }
  int getMonth() { return _month; }
  std::string getMonthName() { return getMonthName(this->getMonth()); }

  // Get year properties
  void setYear(int year) { _year = year; }
  int getYear() { return _year; };

  void setSeparator(std::string separator) { _separator = separator; }
  std::string getSeparator() { return _separator; }

  // *: Setting date methods

  // Set date to today's date
  void setToday(std::string separator = "/") {
    setDate(getCurrentDate(separator), separator);
  }

  void setDate(int day, int month, int year, std::string separator = "/") {
    setDay(day, month, year);
    setMonth(month);
    setYear(year);
    setSeparator(separator);
  }
  void setDate(std::string date, std::string separator = "/") {
    vector<std::string> vDate = Mstring::split(date, separator);

    short day = std::stoi(vDate.at(0));
    short month = std::stoi(vDate.at(1));
    short year = std::stoi(vDate.at(2));

    setDate(day, month, year, separator);
  }
  void setDate(Date date, std::string separator = "/") {
    setDate(date.getDay(), date.getMonth(), date.getYear(), separator);
  }

  // *: Print methods
  // Print any given date object, you have to send separator
  static void print(Date date, std::string separator) {
    std::cout << convertDateToString(date, separator) << '\n';
  }
  // print date from string, must send the operator
  static void print(std::string date, std::string separator) {
    print(convertStringToDate(date, separator), separator);
  }
  // print date from current object you can send operator
  void print(std::string separator) { print(*this, separator); }
  // Print date using current separator
  void print() { print(*this, this->getSeparator()); }

  // *: Converting methods
  // Converting String to date object
  static Date convertStringToDate(std::string date,
                                  std::string separator = "/") {
    Date d;
    d.setDate(date, separator);
    return d;
  }

  // Convert from date object to string
  static std::string convertDateToString(Date &date,
                                         const std::string &separator) {
    std::string result = "";
    result += std::to_string(date.getDay()) + separator;
    result += std::to_string(date.getMonth()) + separator;
    result += std::to_string(date.getYear());
    return result;
  }
  static std::string convertDateToString(Date &date) {
    return convertDateToString(date, date.getSeparator());
  }

  // *: Day methods

  // Get today's date
  static Date getCurrentDate(std::string separator = "/") {
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900, separator);
  }

  // Return date from number of days from (1 / 1 / given year)
  static std::string getDateFromNumberOfDays(int days, int year) {
    int d = days;
    int m = 1;
    int y = year;

    short monthDays = getMonthDays(m, y);

    while (d > monthDays) {
      d = d - monthDays;
      m++;
      if (m == 13) {
        m = 1;
        y++;
      }

      monthDays = getMonthDays(m, y);
    }

    std::string date = "";
    date += to_string(d) + '/';
    date += to_string(m) + '/';
    date += to_string(y);
    // return Date(d, m, y);
    return date;
  }

  static vector<std::string> getDaysArray() {
    std::vector<std::string> daysArray = {"Sun", "Mon", "Tue", "Wed",
                                          "Thu", "Fri", "Sat"};
    return daysArray;
  }

  static short getDayIndexFromDaysArray(std::string dayName) {
    Mstring::capitalize(dayName);

    for (short i = 0; i < getDaysArray().size(); i++) {
      if (dayName == getDaysArray().at(i)) {
        return i;
      }
    }

    return -1;
  }

  // Check if the given int is valid day
  static bool isValidDayOrder(int day) { return (1 <= day && day <= 7); }

  // Check if the given string is a valid day name
  static bool isValidDayOrder(std::string dayName) {
    Mstring::capitalize(dayName);
    for (const std::string &name : getDaysArray()) {
      if (name == dayName) {
        return true;
      }
    }
    return false;
  }

  // Get day name in calender from given date
  static std::string getDayName(const int &day, const int &month,
                                const int &year) {
    if (!isValidDay(day, month, year)) {
      return "Sun";
    }
    return getDaysArray().at(getDayOrderInWeek(day, month, year));
  }

  // Get Day Name in the calender from given string date
  static std::string getDayName(std::string date, std::string separator) {
    Date d = convertStringToDate(date, separator);
    return getDayName(d.getDay(), d.getMonth(), d.getYear());
  }

  static short getDayOrderInWeek(short day, short month, short year) {
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + 12 * a - 2;
    short dayIndex = (day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;

    return dayIndex;
  }

  static bool isValidDay(const int &day, const int &month, const int &year) {
    int monthDays = getMonthDays(month, year);
    return (1 <= day && day <= monthDays);
  }

  static void increaseByOneDay(Date &date) {
    int test = date.getDay() + 1;
    if (test > date.getMonthDays()) {
      date.setDay(1);
      increaseByOneMonth(date);
    } else {
      date.setDay(test);
    }
  }
  void increaseByOneDay() { increaseByOneDay(*this); }

  static void decreaseByOneDay(Date &date) {
    int test = date.getDay() - 1;
    if (test == 0) {
      int lastMonthDays = 0;
      if (date.getMonth() == 1) {
        lastMonthDays = getMonthDays(12, date.getYear());
      }
      lastMonthDays = getMonthDays(date.getMonth() - 1, date.getYear());
      date.setDay(lastMonthDays);

      decreaseByOneMonth(date);
    } else {
      date.setDay(test);
    }
  }
  void decreaseByOneDay() { decreaseByOneDay(*this); }

  // Adding day to date
  static void increaseByXDays(const int days, Date &date) {
    for (int i = 1; i <= days; i++) {
      date.increaseByOneDay();
    }
  }
  void increaseByXDays(int numberOfDays) {
    increaseByXDays(numberOfDays, *this);
  }

  static void decreaseByXDays(const int daysToRemove, Date &date) {
    for (int i = 1; i <= daysToRemove; i++) {
      date.decreaseByOneDay();
    }
  }
  void decreaseByXDays(int daysToRemove) {
    decreaseByXDays(daysToRemove, *this);
  }

  static short daysUntilEndOfWeek(Date date) {
    short days = 0;
    while (date.getDayName() != "Sat") {
      days++;
      date.increaseByOneDay();
    }
    return days;
  }
  short daysUntilEndOfWeek() { return daysUntilEndOfWeek(*this); }

  static bool isLastDayInMonth(Date &date) {
    return date.getDay() == date.getMonthDays();
  }
  bool isLastDayInMonth() { return isLastDayInMonth(*this); }

  static int daysUntilEndOfMonth(Date date) {
    return date.getMonthDays() - date.getDay();
  }
  int daysUntilEndOfMonth() { return daysUntilEndOfMonth(*this); }

  static int daysUntilEndOfYear(Date date) {
    int days = 0;
    while (!date.isEndOfYear()) {
      days++;
      date.increaseByOneDay();
    }
    return days;
  }
  bool daysUntilEndOfYear() { return daysUntilEndOfYear(*this); }

  static short getDayOrderInYear(Date &date) {
    return differenceBetweenDates(Date(1, 1, date.getYear()), date);
  }
  short getDayOrderInYear() { return getDayOrderInYear(*this); }

  static short calculateBusinessDays(Date from, Date to) {
    if (isDate1AfterDate2(to, from)) {
      return -1;
    }
    short days = 0;
    while (!areDatesEqual(from, to)) {
      if (from.isBusinessDay()) {
        days++;
      }
      from.increaseByOneDay();
    }
    return days;
  }
  short calculateBusinessDays(Date to) {
    return calculateBusinessDays(*this, to);
  }

  static short calculateVacationDays(Date from, Date to) {
    if (isDate1AfterDate2(to, from)) {
      return -1;
    }
    short days = 0;
    while (!areDatesEqual(from, to)) {
      if (from.isWeekEnd()) {
        days++;
      }
      from.increaseByOneDay();
    }
    return days;
  }
  short calculateVacationDays(Date to) {
    return calculateVacationDays(*this, to);
  }

  // *: Week methods
  static void increaseByOneWeek(Date &date) { date.increaseByXDays(7); }
  void increaseByOneWeek() { increaseByOneWeek(*this); }

  static void decreaseByOneWeek(Date &date) { date.decreaseByXDays(7); }
  void decreaseByOneWeek() { decreaseByOneWeek(*this); }

  static void increaseByXWeeks(const int &weeks, Date &date) {
    date.increaseByXDays(weeks * 7);
  }
  void increaseByXWeeks(const int &weeks) { increaseByXWeeks(weeks, *this); }

  static void decreaseByXWeeks(const int &weeksToRemove, Date &date) {
    date.decreaseByXDays(weeksToRemove * 7);
  }
  void decreaseByXWeeks(const int &weeksToRemove) {
    decreaseByXWeeks(weeksToRemove, *this);
  }

  static bool isEndOfWeek(Date &date) { return (date.getDayName() == "Sat"); }
  bool isEndOfWeek() { return isEndOfWeek(*this); }

  static bool isWeekEnd(Date &date) {
    const std::string dayName = date.getDayName();
    return (dayName == "Fri" || dayName == "Sat");
  }
  bool isWeekEnd() { return isWeekEnd(*this); }

  static bool isBusinessDay(Date &date) { return !isWeekEnd(date); }
  bool isBusinessDay() { return isBusinessDay(*this); }

  // *: Month methods
  static short getMonthDays(short month, short year) {
    if (month < 1 || month > 12) {
      return -1;
    }

    short numberOfDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2) ? (isLeapYear(year) ? 29 : 28)
                        : numberOfDays[month - 1];
  }
  short getMonthDays() {
    return getMonthDays(this->getMonth(), this->getYear());
  }

  static bool isValidMonth(const int &month) {
    return (1 <= month && month <= 12);
  }

  static vector<std::string> getMonthsArray() {
    vector<std::string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    return months;
  }

  static std::string getMonthName(const int &month) {
    if (!isValidMonth(month)) {
      return "Jan";
    }
    return getMonthsArray().at(month - 1);
  }

  static void increaseByOneMonth(Date &date) {
    int test = date.getMonth() + 1;

    if (test > 12) {
      date.setMonth(1);
      increaseByOneYear(date);
    } else {
      date.setMonth(test);
    }

    const int monthDays = date.getMonthDays();
    if (date.getDay() > monthDays) {
      date.setDay(monthDays);
    }
  }
  void increaseByOneMonth() { increaseByOneMonth(*this); }

  static void decreaseByOneMonth(Date &date) {
    int test = date.getMonth() - 1;

    if (test == 0) {
      date.setMonth(12);
      decreaseByOneYear(date);
    } else {
      date.setMonth(test);
    }

    const int monthDays = date.getMonthDays();
    if (date.getDay() > monthDays) {
      date.setDay(monthDays);
    }
  }
  void decreaseByOneMonth() { decreaseByOneMonth(*this); }

  static void increaseByXMonths(const int &months, Date &date) {
    for (int i = 1; i <= months; i++) {
      date.increaseByOneMonth();
    }
  }
  void increaseByXMonths(const int &months) {
    increaseByXMonths(months, *this);
  }

  static void decreaseByXMonths(const int &monthsToRemove, Date &date) {
    for (int i = 1; i <= monthsToRemove; i++) {
      date.decreaseByOneMonth();
    }
  }
  void decreaseByXMonths(const int &monthsToRemove) {
    decreaseByXMonths(monthsToRemove, *this);
  }

  static unsigned short getMonthHours(short month, short year) {
    return getMonthDays(month, year) * 24;
  }
  unsigned short getMonthHours() {
    return getMonthHours(this->getMonth(), this->getYear());
  }

  static unsigned short getMonthMinuets(short month, short year) {
    return getMonthHours(month, year) * 60;
  }
  unsigned short getMonthMinuets() {
    return getMonthMinuets(this->getMonth(), this->getYear());
  }

  static unsigned getMonthSeconds(short month, short year) {
    return getMonthMinuets(month, year) * 60;
  }
  unsigned short getMonthSeconds() {
    return getMonthSeconds(this->getMonth(), this->getYear());
  }

  static void printMonthData(short month, short year) {
    printf("Number of days in month: %d, year: %d   : %d\n", month, year,
           getMonthDays(month, year));
    printf("Number of hours in month: %d, year: %d  : %d\n", month, year,
           getMonthHours(month, year));
    printf("Number of minutes in month: %d, year: %d: %d\n", month, year,
           getMonthMinuets(month, year));
    printf("Number of seconds in month: %d, year: %d: %d\n", month, year,
           getMonthSeconds(month, year));
  }
  void printMonthData() { printMonthData(this->getMonth(), this->getYear()); }

  static void printMonthCalender(short month, short year) {
    cout << "_______________" << getMonthName(month) << "_______________\n\n";

    // Print Day Names
    for (short i = 0; i <= 6; i++) {
      cout << getDayName(i, month, year) << "  ";
    }
    cout << endl;

    // Print Spaces before first day
    short dayOrder = getDayOrderInWeek(1, month, year);
    short spaces = (dayOrder * 3) + (2 * dayOrder);

    for (short i = 1; i <= dayOrder; i++) {
      cout << "     ";
    }

    for (short i = 1; i <= getMonthDays(month, year); i++) {
      cout << setw(3) << i << "  ";

      if (dayOrder++ == 6) {
        dayOrder = 0;
        cout << endl;
      }
    }
    cout << endl;

    cout << "_________________________________\n";
  }
  void printMonthCalender() {
    printMonthCalender(this->getMonth(), this->getYear());
  }

  static bool isLastMonth(Date &date) { return date.getMonth() == 12; }
  bool isLastMonth() { return isLastMonth(*this); }

  // *: Year methods
  static bool isLeapYear(short year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
  }
  bool isLeapYear() { return isLeapYear(this->getYear()); }

  static void increaseByOneYear(Date &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() + 1);
  }
  void increaseByOneYear() { increaseByOneYear(*this); }

  static void decreaseByOneYear(Date &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() - 1);
  }
  void decreaseByOneYear() { decreaseByOneYear(*this); }

  static void increaseByXYears(const int &years, Date &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() + years);
  }
  void increaseByXYears(const int &years) { increaseByXYears(years, *this); }

  static void decreaseByXYears(const int &yearsToRemove, Date &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() - yearsToRemove);
  }
  void decreaseByXYears(const int &yearsToRemove) {
    decreaseByXYears(yearsToRemove, *this);
  }

  static short getYearDays(const short &year) {
    return isLeapYear(year) ? 366 : 365;
  }
  short getYearDays() { return getYearDays(this->getYear()); }

  static short getYearHours(short year) { return getYearDays(year) * 24; }
  short getYearHours() { return getYearHours(this->getYear()); }

  static unsigned getYearMinuets(short year) { return getYearHours(year) * 60; }
  unsigned getYearMinuets() { return getYearMinuets(this->getYear()); }

  static unsigned getYearSeconds(short year) {
    return getYearMinuets(year) * 60;
  }
  unsigned getYearSeconds() { return getYearSeconds(this->getYear()); }

  static void printYearData(short year) {
    printf("Number of days in %d   : %d\n", year, getYearDays(year));
    printf("Number of hours in %d  : %d\n", year, getYearHours(year));
    printf("Number of minuets in %d : %d\n", year, getYearMinuets(year));
    printf("Number of seconds in %d: %d\n", year, getYearSeconds(year));
  }
  void printYearData() { printYearData(this->getYear()); }

  static void printYearCalender(short year) {
    cout << "_________________________________\n";
    cout << "_______________" << year << "_______________\n\n";
    cout << "_________________________________\n";
    for (short i = 1; i <= 12; i++) {
      printMonthCalender(i, year);
    }
  }
  void printYearCalender() { printYearCalender(this->getYear()); }

  static bool isEndOfYear(Date &date) {
    return date.isLastMonth() && date.isLastDayInMonth();
  }
  bool isEndOfYear() { return isEndOfYear(*this); }

  //* : Other methods
  static void swapDates(Date &d1, Date &d2) {
    Date x = d1;
    d1 = d2;
    d2 = x;
  }

  static bool isDate1AfterDate2(Date &d1, Date &d2) {
    return ((d1.getYear() > d2.getYear()) ? true
            : d1.getYear() == d2.getYear()
                ? d1.getMonth() > d2.getMonth() ? true
                  : d1.getMonth() == d2.getMonth()
                      ? d1.getDay() > d2.getDay() ? true : false
                      : false
                : false);
  }

  static bool areDatesEqual(Date &d1, Date &d2) {
    return (d1.getYear() == d2.getYear() && d1.getMonth() == d2.getMonth() &&
            d1.getDay() > d2.getDay());
  }

  static int differenceBetweenDates(Date d1, Date d2) {
    int difference = 0;
    bool multiple = false;

    if (isDate1AfterDate2(d1, d2)) {
      swapDates(d1, d2);
      multiple = true;
    }

    while (!areDatesEqual(d1, d2)) {
      d1.increaseByOneDay();
      difference++;
    }

    return multiple ? difference * -1 : difference;
  }

  static unsigned calculateAgeInDays(Date birthDay) {
    Date today = getCurrentDate();
    int ageInDays = 0;
    while (isDate1AfterDate2(today, birthDay)) {
      today.increaseByOneDay();
      ageInDays++;
    }

    return ageInDays;
  }

  static bool isDateInsideRange(Date date, Date d1, Date d2) {
    if (areDatesEqual(date, d1) || areDatesEqual(date, d2))
      return true;
    if (isDate1AfterDate2(date, d1) && isDate1AfterDate2(d2, date))
      return true;
    return false;
  }

  static std::string getTodayTimeAndDate() {
    // todo: add format options yyyy/mm/dd - hh:mm:ss
    time_t t = time(0);
    tm *now = localtime(&t);

    std::string time = "";

    time += std::to_string(now->tm_year + 1900) + '/';
    time += std::to_string(now->tm_mon + 1) + '/';
    time += std::to_string(now->tm_mday) + " - ";
    time += std::to_string(now->tm_hour) + ":";
    time += std::to_string(now->tm_min) + ":";
    time += std::to_string(now->tm_sec);

    return time;
  }
};
