// ReservationInquiry.h
// ReservationInquiry class definition.
#ifndef RESERVATION_INQUIRY_H
#define RESERVATION_INQUIRY_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition

class ReservationInquiry
{
public:
   ReservationInquiry( ReservationDatabase &, AvailRoomDatabase & );
   void execute();
private:
   ReservationDatabase &reservationDatabase;
   AvailRoomDatabase &availableRoomDatabase;

}; // end class ReservationInquiry

#endif // RESERVATION_INQUIRY_H