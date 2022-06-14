// Date.cpp
// Member-function definitions for class Date.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#include "Date.h"

extern bool leapYear( int year );

Date::Date()
{
   year = 2000;
   month = 0;
   day = 0;
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000; // sets year
}

void Date::setMonth( int m )
{
   month = ( m <= 12 && m >= 1 ) ? m : 1; // sets month
}

void Date::setDay( int d )
{
   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if( month == 2 && leapYear( year ) )
      day = ( d <= 29 && d >= 1 ) ? d : 1;
   else
      day = ( d <= days[ month ] && d >= 1 ) ? d : 1;
}

int Date::getYear() const
{
   return year;
}

int Date::getMonth() const
{
   return month;
}

int Date::getDay() const
{
   return day;
}

bool Date::operator==( const Date &date2 )
{
   return ( year == date2.year && month == date2.month && day == date2.day );
}

bool Date::operator<( const Date &date2 )
{
   if( year < date2.year )
      return true;
   if( year > date2.year )
      return false;

   if( month < date2.month )
      return true;
   if( month > date2.month )
      return false;

   if( day < date2.day )
      return true;

   return false;
}

bool Date::operator<=( const Date &date2 )
{
   return ( *this < date2 ) || ( *this == date2 );
}

bool Date::operator>=( const Date &date2 )
{
   return !( *this < date2 );
}

// return *this - date2 provided that *this > date2
int Date::operator-( const Date &date2 )
{
    int num = 0; //¬Û®t¤Ñ¼Æ
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (*this <= date2)
        return 0;
    else
    {
        int gap_year = getYear() - date2.getYear();
        if (gap_year != 0)
        {
            int t_num = 0;
            for (int i = 0; i < gap_year; ++i)
            {
                if (leapYear(date2.getYear() + i))
                    t_num += 366;
                else
                    t_num += 365;
            }

            int t_count = 0;

            if (date2.getMonth() > getMonth())
            {
                if (getDay() >= date2.getDay())
                {
                    int gap_month = date2.getMonth() - getMonth();
                    Date tmp;
                    for (int i = 0; i < gap_month; ++i)
                    {
                        tmp.setDay(date2.getMonth() + i);
                        t_count += tmp.getDay();
                    }
                    t_count += getDay() - date2.getDay();
                }
                else
                {
                    Date tmp;
                    int gap_month = date2.getMonth() - getMonth();
                    int days = getDay();
                    for (int i = 1; i <= gap_month; ++i)
                    {
                        tmp.setDay(date2.getMonth() - i);
                        days += tmp.getDay();
                    }
                    t_count = days - date2.getDay();
                }

                num = t_num - t_count;
            }
            else
            {
                if (getDay() >= date2.getDay())
                {
                    int gap_month = getMonth() - date2.getMonth();
                    for (int i = 0; i < gap_month; ++i)
                    {
                        int d = days[date2.getMonth() + i];
                        if ((date2.getMonth() + i) == 2 && leapYear(date2.getYear()))
                            ++d;
                        t_count += d;
                    }
                    t_count += getDay() - date2.getDay();
                }
                else
                {
                    int gap_month = getMonth() - date2.getMonth();
                    int tmpdays = getDay();
                    for (int i = 1; i <= gap_month; ++i)
                    {
                        int d = days[date2.getMonth() - i];
                        if ((date2.getMonth() - i) == 2 && leapYear(date2.getYear()))
                            ++d;
                        tmpdays += d;
                    }
                    t_count = tmpdays - date2.getDay();
                }

                num = t_num + t_count;
            }
        }
        else
        {
            if (getDay() >= date2.getDay())
            {
                int gap_month = getMonth() - date2.getMonth();
                for (int  i = 0; i < gap_month; ++i)
                {
                    int d = days[date2.getMonth() + i];
                    if ((date2.getMonth() + i) == 2 && leapYear(date2.getYear()))
                        ++d;
                    num += d;
                }
                num += getDay() - date2.getDay();
            }
            else
            {
                int gap_month = getMonth() - date2.getMonth();
                int tmpdays = getDay();
                for (int i = 1; i <= gap_month; ++i)
                {
                    int d = days[date2.getMonth() - i];
                    if ((date2.getMonth() - i) == 2 && leapYear(date2.getYear()))
                        ++d;
                    tmpdays += d;
                }
                num = tmpdays - date2.getDay();
            }
        }
    }
    return num;
}