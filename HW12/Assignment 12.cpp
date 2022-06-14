// EvergreenLaurelHotel.cpp
// Member-function definitions for class EvergreenLaurelHotel.
#include <iostream>
#include <iomanip>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition
#include "ReservationInquiry.h" // ReservationInquiry class definition

int inputAnInteger( int begin, int end ); // input an integer in the range [ begin, end ]

Date computeCurrentDate(); // return the current date

bool leapYear( int year ); // if the year is a leap year, return true; otherwise, return false

int main()
{
   cout << "Evergreen Laurel Hotel Online Reservation System\n";

   enum MenuOption { MAKE_RESERVATION = 1, RESERVATION_INQUIRY, EXIT };
   bool userExited = false; // user has not chosen to exit

   // loop while user has not chosen option to exit system
   while( !userExited )
   {
      ReservationDatabase reservationDatabase;
      AvailRoomDatabase availableRoomDatabase;

      MakeReservation makeReservation( reservationDatabase, availableRoomDatabase );
      ReservationInquiry reservationInquiry( reservationDatabase, availableRoomDatabase );

      // show main menu and get user selection
      cout << "\n1 - Making Reservation\n";
      cout << "2 - Reservation Inquiry\n";
      cout << "3 - End\n\n";

      int mainMenuSelection;
      do cout << "Enter your choice: (1~3): ";
      while( ( mainMenuSelection = inputAnInteger( 1, 3 ) ) == -1 );

      // decide how to proceed based on user's menu selection
      switch( mainMenuSelection )
      {
      case MAKE_RESERVATION:
         makeReservation.execute();
         break;
      case RESERVATION_INQUIRY:
         reservationInquiry.execute();
         break;
      case EXIT: // user chose to terminate session
         cout << "\nExiting the system...\n\n";
         userExited = true; // this ATM session should end
         break;
      default: // user did not enter an integer from 1-3
         cout << "\nYou did not enter a valid selection. Try again." << endl;
         break;
      }
   }

   system( "pause" );
}

int inputAnInteger( int begin, int end )
{
   char string[ 80 ];
   cin.getline( string, 80, '\n' );

   if( strlen( string ) == 0 )
      exit( 0 );

   for( unsigned int i = 0; i < strlen( string ); i++ )
      if( string[ i ] < '0' || string[ i ] > '9' )
         return -1;

   int number = atoi( string );

   if( number >= begin && number <= end )
      return number;
   else
      return -1;
}

Date computeCurrentDate()
{
   tm structuredTime;
   time_t rawTime = time( 0 );
   localtime_s( &structuredTime, &rawTime );

   int year = structuredTime.tm_year + 1900;
   int month = structuredTime.tm_mon + 1;
   int day = structuredTime.tm_mday;

   Date currentDate;
   currentDate.setYear( year );
   currentDate.setMonth( month );
   currentDate.setDay( day );

   return currentDate;
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}