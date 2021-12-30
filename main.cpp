#include <exception>
#include <iostream>
#include <sstream>


/**
 * @brief   Проверяет дату в строковом формате на корректность
 * @param[in]   str_date   Дата в строковом формате
 * @return   true   Дата корректна
 * @return   false   Дата некорректна
 */
bool parsing_of_date(const std::string& str_date)
{
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

   return flag;
}


int main()
{
   std::stringstream s("2019--12-+14");
   if (!parsing_of_date(s.str()))
      std::cout << "error" << std::endl;

   return 0;
}