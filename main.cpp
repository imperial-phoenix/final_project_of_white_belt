#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>


/************************************************************
*                     DATE IMPLEMENTATION                   *
************************************************************/

class Date
{
public:
   Date(int Year, int Month, int Day) : year{Year}, month{Month}, day{Day} {};

   int GetYear() const { return this->year; }
   int GetMonth() const { return this->month; }
   int GetDay() const { return this->day; }

private:
   int year;
   int month;
   int day;
};


bool operator<(const Date& lhs, const Date& rhs)
{
   if (lhs.GetYear() < rhs.GetYear()) return true;
   else if (lhs.GetMonth() < rhs.GetMonth()) return true;
   else if (lhs.GetDay() < rhs.GetDay()) return true;
   else return false;
}


std::ostream& operator<<(std::ostream& out, const Date& date)
{
   out << std::setfill('0');
   out << std::setw(4) << date.GetYear() << "-" <<  std::setw(4) << date.GetMonth() << "-" << std::setw(4) << date.GetDay();
   return out;
}


/**
 * @brief   Парсинг даты из строкового формата в формат класса Date
 * @param[in]   str_date   Дата в строковом формате
 * @return   В случае корректности данных возвращается дата, в ином случае бросается исключение
 */
Date parsing_of_date(const std::string& str_date)
{
   // Проверка на валидность формата
   std::istringstream stream_date(str_date);
   bool flag{true};

   int year;
   stream_date >> year;
   flag &= !stream_date.fail();
   flag &= stream_date.peek() == '-';
   stream_date.ignore(1);

   int month;
   stream_date >> month;
   flag &= !stream_date.fail();
   flag &= stream_date.peek() == '-';
   stream_date.ignore(1);

   int day;
   stream_date >> day;
   flag &= !stream_date.fail();
   flag &= stream_date.eof();

   if (!flag)
      throw std::logic_error("Wrong date format: " + str_date);

   // Проверка на корректность данных
   if (month < 1 || month > 12)
      throw std::logic_error("Month value is invalid: " + std::to_string(month));

   if (day > 31 || 1 > day)
      throw std::logic_error("Day value is invalid: " + std::to_string(day));

   return Date(year, month, day);
}


/************************************************************
*                   DATABASE IMPLEMENTATION                 *
************************************************************/

class Database
{
public:
   void add_event(const Date& date, const std::string& event);
   bool delete_event(const Date& date, const std::string& event);
   int delete_date(const Date& date);
   void find(const Date& date) const;
   void print() const;

private:
   std::map<Date, std::set<std::string>> data;
};


int main()
{
   Database db;

   std::string command;
   while (std::getline(std::cin, command))
   {
      
   }

   return 0;
}