// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

ReservationDatabase::ReservationDatabase()
{
	loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
	saveToReservationFile();
}

void ReservationDatabase::loadReservations()
{
	ifstream inFile("Reservations.dat", ios::in | ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	inFile.seekg(0, ios::beg);

	while (!inFile.eof())
	{
		Reservation tmp;
		Date t;
		inFile.read(reinterpret_cast<char*>(&tmp), sizeof(Reservation));
		if (tmp.getCheckInDate() == t);
		else
			reservations.push_back(tmp);
	}
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

int ReservationDatabase::numReservations( string idNumber ) //看這個ID有訂多少房間
{
	int num = 0;
	for (vector< Reservation >::iterator it = reservations.begin(); it < reservations.end(); it++)
		if (it->equalID(idNumber, it->getIDNumber()))
			num++;

	return num;
}

void ReservationDatabase::displayReservations( string idNumber )
{
	cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";

   for( vector< Reservation >::iterator it = reservations.begin(); it < reservations.end(); it++ )
      if( it->equalID( idNumber, it->getIDNumber() ) )
         it->displayReservation();
}

void ReservationDatabase::saveToReservationFile()
{
	ofstream inFile("Reservations.dat", ios::out | ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}


	for (int i = 0; i < reservations.size(); ++i)
	{
		inFile.write(reinterpret_cast<char*>(&reservations[i]), sizeof(Reservation));
	}

	inFile.close();
}