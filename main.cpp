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
   return (lhs.GetYear() * 12 * 31 + lhs.GetMonth() * 31 + lhs.GetDay()) <
   (rhs.GetYear() *12 *31 + rhs.GetMonth() * 31 + rhs.GetDay());
}


std::ostream& operator<<(std::ostream& out, const Date& date)
{
   out << std::setfill('0');
   out << std::setw(4) << date.GetYear() << "-" <<  std::setw(2) << date.GetMonth() << "-" << std::setw(2) << date.GetDay();
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


void Database::add_event(const Date& date, const std::string& event)
{
   this->data[date].insert(event);
}


bool Database::delete_event(const Date& date, const std::string& event)
{
   if (this->data.count(date) > 0 && this->data.at(date).count(event) > 0)
   {
      this->data.at(date).erase(event);
      return true;
   }
   else
   {
      return false;
   }
}


int Database::delete_date(const Date& date)
{
   if (this->data.count(date) > 0)
   {
      int result{static_cast<int>(this->data.at(date).size())};
      this->data.erase(date);
      return result;
   }
   else
   {
      return 0;
   }
}


void Database::find(const Date& date) const
{
   if (this->data.count(date) > 0 && !this->data.at(date).empty())
   {
      for (const std::string& event : this->data.at(date))
      {
         std::cout << event << std::endl;
      }
   }
}


void Database::print() const
{
   for (const auto& pair : this->data)
   {
      for (const std::string& event : pair.second)
      {
         std::cout << pair.first << " " << event << std::endl;
      }
   }
}


int main()
{
   try
   {
      Database db;

      std::string command;
      while (std::getline(std::cin, command))
      {
         std::stringstream stream_command{command};

         std::string operation_code;
         stream_command >> operation_code;

         if ("Add" == operation_code)
         {
            std::string str_date;
            stream_command >> str_date;
            Date date{parsing_of_date(str_date)};
            std::string event;
            stream_command >> event;
            db.add_event(date, event);
         }
         else if ("Print" == operation_code)
         {
            db.print();
         }
         else if ("Del" == operation_code)
         {
            std::string str_date;
            stream_command >> str_date;
            Date date{parsing_of_date(str_date)};
            std::string event;
            if (!stream_command.eof())
            {
               stream_command >> event;
            }
            if (event.empty())
            {
               std::cout << "Deleted " << db.delete_date(date) << " events" << std::endl;
            }
            else
            {
               if (db.delete_event(date, event))
               {
                  std::cout << "Deleted successfully" << std::endl;
               }
               else
               {
                  std::cout << "Event not found" << std::endl;
               }
            }
         }
         else if ("Find" == operation_code)
         {
            std::string str_date;
            stream_command >> str_date;
            Date date{parsing_of_date(str_date)};
            db.find(date);
         }
         else if ("" != operation_code)
         {
            throw std::logic_error("Unknown command: " + operation_code);
         }
      }
   }
   catch(const std::exception& ex)
   {
      std::cout << ex.what() << std::endl;
   }

   return 0;
}