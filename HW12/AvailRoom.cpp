// AvailRoom.cpp
// Member-function definitions for class AvailRoom.
#include "AvailRoom.h" // AvailRoom class definition

int totalNumRooms[ 6 ] = { 0, 9, 5, 3, 5, 4 }; // total number of rooms for each room type

AvailRoom::AvailRoom()
{
   for( int i = 0; i < 6; i++ )
      availRooms[ i ] = totalNumRooms[ i ];
}

void AvailRoom::setDate( int year, int month, int day )
{
   date.setYear( year );
   date.setMonth( month );
   date.setDay( day );
}

Date AvailRoom::getDate()
{
   return date;
}

void AvailRoom::initAvailRooms()
{
   for( int i = 0; i < 6; i++ )
      availRooms[ i ] = totalNumRooms[ i ];
}

int AvailRoom::getAvailRoom( int i )
{
   return availRooms[ i ];
}

void AvailRoom::decreaseAvailRooms( int roomType, int numRooms )
{
   availRooms[ roomType ] -= numRooms;
}