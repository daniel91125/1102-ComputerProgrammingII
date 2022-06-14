// AvailRoom.h
// AvailRoom class definition. Represents the number of available rooms of each type for one day.
#ifndef AVAIL_ROOM_H
#define AVAIL_ROOM_H

#include "Date.h" // Date class definition

class AvailRoom
{
public:
   AvailRoom();
   void setDate( int year, int month, int day );
   Date getDate();
   void initAvailRooms();
   int getAvailRoom( int i ); // return availRooms[ i ]
   void decreaseAvailRooms( int roomType, int numRooms ); // availRooms[ roomType ] -= numRooms
private:
   Date date;
   int availRooms[ 6 ] = {}; // number of available rooms for each room type
}; // end class AvailRoom

#endif // AVAIL_ROOM_H