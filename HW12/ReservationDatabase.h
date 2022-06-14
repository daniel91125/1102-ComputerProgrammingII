// ReservationDatabase.h
// ReservationDatabase class definition. Represents reservation database.
#ifndef RESERVATION_DATABASE_H
#define RESERVATION_DATABASE_H

#include <vector>
#include "Reservation.h" // Reservation class definition

class ReservationDatabase
{
public:
   ReservationDatabase();

   ~ReservationDatabase();

   // return the number of reservations for idNumber
   int numReservations( string idNumber );

   // display all reservations information for idNumber
   void displayReservations( string idNumber );

   // call reservations.push_back( newReservation )
   void pushBack( Reservation newReservation );

private:
   vector< Reservation > reservations; // vector of the reservations

   // read reservations information whose checkInDate are after or equal to currentDate,
   // from the file Reservations.dat
   void loadReservations();

   // save all reservations information into the file Reservations.dat
   void saveToReservationFile();

}; // end class ReservationDatabase

#endif // RESERVATION_DATABASE_H