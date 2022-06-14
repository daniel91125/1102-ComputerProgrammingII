// ReservationInquiry.cpp
// Member-function definitions for class ReservationInquiry.
#include <iostream>
#include <string>
using namespace std;
#include "ReservationInquiry.h" // ReservationInquiry class definition

ReservationInquiry::ReservationInquiry( ReservationDatabase &theReservationDatabase,
                                        AvailRoomDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomDatabase( theAvailableRoomsDatabase )
{
}

void ReservationInquiry::execute()
{
   string idNumber;
   cout << "\nEnter your ID number: ";
   cin >> idNumber;
   cin.ignore();

   if( reservationDatabase.numReservations( idNumber ) )
      reservationDatabase.displayReservations( idNumber );
   else
      cout << "\nSorry! You do not have reservations!\n";
}