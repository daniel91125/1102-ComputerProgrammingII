// MakeReservation.h
// MakeReservation class definition.
#ifndef MAKE_RESERVATION_H
#define MAKE_RESERVATION_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition

class MakeReservation
{
public:
   MakeReservation( ReservationDatabase &, AvailRoomDatabase & );
   void execute();
private:
   Reservation newReservation;
   ReservationDatabase &reservationDatabase;
   AvailRoomDatabase &availableRoomDatabase;

   // compute availableMonths
   void computeAvailableMonths( Date currentDate, Date availableMonths[] );

   // input check in date by user, and put them into checkInDate
   void inputCheckInDates( Date &checkInDate, Date currentDate,
        Date availableMonths[], int &checkInYMCode, int &firstDay, int &lastDay );

   // input check out date by user, and put them into checkOutDate
   void inputCheckOutDates( Date &checkOutDate, Date checkInDate,
        Date availableMonths[], int checkInYMCode, int firstDay, int lastDay );

}; // end class MakeReservation

#endif // MAKE_RESERVATION_H