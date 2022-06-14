// AvailRoomDatabase.cpp
// Member-function definitions for class AvailRoomDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition

extern bool leapYear(int year);
extern Date computeCurrentDate();
//char availFileName[] = "Available Rooms 2021-11-24.dat";
//char availFileName[] = "Available Rooms 2022-2-22.dat";
char availFileName[] = "Available Rooms 2022-5-23.dat";
//char availFileName[] = "Available Rooms 2022-5-28.dat";
//char availFileName[] = "Available Rooms blank.dat";

AvailRoomDatabase::AvailRoomDatabase()
{
	loadAvailableRooms();

	if (availRooms.size() == 0)
		initAvailRooms(); // create available rooms information for 6 months
	else
		appendAvailRooms(); // append new available rooms information
}

AvailRoomDatabase::~AvailRoomDatabase()
{
	saveAvailableRooms();
}

void AvailRoomDatabase::loadAvailableRooms()
{
	ifstream inFile(availFileName, ios::in | ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	inFile.seekg(0, ios::beg);

	while (!inFile.eof())
	{
		AvailRoom tmp;
		inFile.read(reinterpret_cast<char*>(&tmp), sizeof(AvailRoom));
		if (tmp.getDate() < computeCurrentDate())
			continue;
		else
			availRooms.push_back(tmp);
	}
}

void AvailRoomDatabase::initAvailRooms()
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Date cur = computeCurrentDate();

	int cur_year = cur.getYear();
	int cur_month = cur.getMonth();
	int cur_days = cur.getDay();

	for (int i = 0; i < 6; ++i) //當今時間往後推六個月
	{
		AvailRoom tmp;
		if (i == 0)
		{
			int d = 0;
			if (cur_month == 2 && leapYear(cur_year))
				d = 29;
			else
				d = days[cur_month];

			for (int j = cur_days; j <= d; ++j)
			{
				tmp.setDate(cur_year, cur_month, j);
				tmp.initAvailRooms();
				availRooms.push_back(tmp);
			}

		}
		else
		{
			int y = cur_year;
			int m = cur_month + i;
			int d = 0;

			if (m > 12)
			{
				m %= 12;
				y += 1;
			}

			if (m == 2 && leapYear(y))
				d = 29;
			else
				d = days[m];

			for (int j = 1; j <= d; ++j)
			{
				tmp.setDate(y, m, j);
				tmp.initAvailRooms();
				availRooms.push_back(tmp);
			}
		}
	}
}

void AvailRoomDatabase::appendAvailRooms() //不滿六個月，要補齊
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Date last = availRooms[availRooms.size() - 1].getDate();
	Date first = availRooms[0].getDate();
	AvailRoom tmp;

	if (last.getMonth() - first.getMonth() + 1 == 6)
		return;

	if (last.getYear() != first.getYear())
	{
		int diff = 0;
		int t1 = 12 - first.getMonth() + 1;
		int t2 = last.getMonth();
		if (t1 + t2 < 6) //不足把日期補齊
		{
			diff = 6 - (t1 + t2); //差幾個月
			for (int i = 1; i <= diff; ++i) 
			{
				int y = last.getYear();
				int m = last.getMonth() + i;
				int d = 0;

				if (m > 12)
				{
					m %= 12;
					y += 1;
				}
				if (m == 2 && leapYear(y))
					d = 29;
				else
					d = days[m];

				for (int j = 1; j <= d; ++j)
				{
					tmp.setDate(y, m, j);
					tmp.initAvailRooms();
					availRooms.push_back(tmp);
				}
			}
		}
	}
	else
	{
		int diff = 0;
		int t1 = last.getMonth() - first.getMonth() + 1;
		if (t1 < 6)
		{
			diff = 6 - t1;
			for (int i = 1; i <= diff; ++i)
			{
				int y = last.getYear();
				int m = last.getMonth() + i;
				int d = 0;

				if (m == 2 && leapYear(y))
					d = 29;
				else
					d = days[m];

				for (int j = 1; j <= d; ++j)
				{
					tmp.setDate(y, m, j);
					tmp.initAvailRooms();
					availRooms.push_back(tmp);
				}
			}
		}
	}
}

void AvailRoomDatabase::displayAvailableRooms(Date checkInDate, Date checkOutDate)
{
	cout << "\nThe number of available rooms of each room type:\n\n";
	cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

	vector< AvailRoom >::iterator checkInIterator;
	vector< AvailRoom >::iterator checkOutIterator;

	findIterators(checkInDate, checkOutDate, checkInIterator, checkOutIterator);

	for (vector< AvailRoom >::iterator it = checkInIterator; it < checkOutIterator; ++it)
		cout << it->getDate().getYear() << "-"
		<< setw(2) << setfill('0') << it->getDate().getMonth() << "-"
		<< setw(2) << it->getDate().getDay()
		<< setw(16) << setfill(' ') << it->getAvailRoom(1)
		<< setw(14) << it->getAvailRoom(2)
		<< setw(19) << it->getAvailRoom(3)
		<< setw(17) << it->getAvailRoom(4)
		<< setw(15) << it->getAvailRoom(5) << "\n";
}

int AvailRoomDatabase::compMinNumRooms(int roomType,
	const Date& checkInDate, const Date& checkOutDate)
{
	vector< AvailRoom >::iterator checkInIterator;
	vector< AvailRoom >::iterator checkOutIterator;

	findIterators(checkInDate, checkOutDate, checkInIterator, checkOutIterator);

	int min = checkInIterator->getAvailRoom(roomType);

	for (; checkInIterator != checkOutIterator; ++checkInIterator)
		if (min > checkInIterator->getAvailRoom(roomType))
			min = checkInIterator->getAvailRoom(roomType);

	return min;
}

void AvailRoomDatabase::decreaseAvailRooms(int roomType, int numRooms,
	const Date& checkInDate, const Date& checkOutDate)
{
	vector< AvailRoom >::iterator checkInIterator;
	vector< AvailRoom >::iterator checkOutIterator;
	
	findIterators(checkInDate, checkOutDate, checkInIterator, checkOutIterator);

	for (; checkInIterator != checkOutIterator; ++checkInIterator)
	{
		checkInIterator->decreaseAvailRooms(roomType, numRooms);
	}
}

void AvailRoomDatabase::saveAvailableRooms()
{
	Date cur = computeCurrentDate();

	ofstream inFile(availFileName, ios::out | ios::binary);
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < availRooms.size(); ++i)
	{
		inFile.write(reinterpret_cast<char*>(&availRooms[i]), sizeof(AvailRoom));
	}

	inFile.close();
}

void AvailRoomDatabase::findIterators(const Date& checkInDate, const Date& checkOutDate,
	vector< AvailRoom >::iterator& checkInIterator,
	vector< AvailRoom >::iterator& checkOutIterator)
{
	for (checkInIterator = availRooms.begin(); checkInIterator != availRooms.end(); ++checkInIterator)
		if (checkInIterator->getDate() == checkInDate)
			break;

	for (checkOutIterator = availRooms.begin(); checkOutIterator != availRooms.end(); ++checkOutIterator)
		if (checkOutIterator->getDate() == checkOutDate)
			break;
}