// AvailRoomDatabase.h
// AvailRoomDatabase class definition.
#ifndef AVAIL_ROOM_DATABASE_H
#define AVAIL_ROOM_DATABASE_H

#include <vector>
#include "AvailRoom.h" // AvailRoom class definition

class AvailRoomDatabase
{
public:
   AvailRoomDatabase();

   ~AvailRoomDatabase();

   // display availableRooms information between checkInDate and checkOutDate
   void displayAvailableRooms( Date checkInDate, Date checkOutDate );

   // return the minimum between availRooms[ first .. last ].numAvailRooms[ roomType ],
   // where availRooms[ first ].date == checkInDate and
   // availRooms[ last ].date == checkOutDate.
   int compMinNumRooms( int roomType, const Date &checkInDate, const Date &checkOutDate );

   // availRooms[ i .. j ].availRooms[ roomType ] -= numRooms, where
   // availRooms[ i ].date == checkInDate and availRooms[ j ].date == checkOutDate - 1
   void decreaseAvailRooms( int roomType, int numRooms,
                            const Date &checkInDate, const Date &checkOutDate );
private:
   vector< AvailRoom > availRooms; // vector of the available rooms for next 6 months

   // read reservations information whose checkInDate are after or equal to currentDate,
   // from the file Reservations.dat
   void loadAvailableRooms();

   // save all reservations information into the file Reservations.dat
   void saveAvailableRooms();

   // create available rooms information for 6 months, starting from currentDate
   // provided that availRooms.size() == 0
   void initAvailRooms();

   // append new available rooms information, provided that availRooms.size() != 0
   void appendAvailRooms();

   // checkInIterator points to availRooms[ i ], where availRooms[ i ].date == checkInDate,
   // checkOutIterator points to availRooms[ j ], where availRooms[ j ].date == checkOutDate
   void findIterators( const Date &checkInDate, const Date &checkOutDate,
                       vector< AvailRoom >::iterator &checkInIterator,
                       vector< AvailRoom >::iterator &checkOutIterator );
}; // end class AvailRoomDatabase

#endif // AVAIL_ROOM_DATABASE_H