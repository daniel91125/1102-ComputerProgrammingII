// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition

extern bool leapYear(int year);
extern Date computeCurrentDate();

MakeReservation::MakeReservation(ReservationDatabase& theReservationDatabase,
	AvailRoomDatabase& theAvailableRoomsDatabase)
	: reservationDatabase(theReservationDatabase),
	availableRoomDatabase(theAvailableRoomsDatabase)
{
}

void MakeReservation::execute()
{
	Date currentDate = computeCurrentDate();

	Date availableMonths[7];

	computeAvailableMonths(currentDate, availableMonths);

	int checkInYMCode;
	int firstDay;
	int lastDay;

	Date checkInDate;
	Date checkOutDate;

	inputCheckInDates(checkInDate, currentDate, availableMonths, checkInYMCode, firstDay, lastDay);
	inputCheckOutDates(checkOutDate, checkInDate, availableMonths, checkInYMCode, firstDay, lastDay);

	cout << "\nCheck in date: " << checkInDate.getYear() << '-'
		<< setw(2) << setfill('0') << checkInDate.getMonth() << '-'
		<< setw(2) << checkInDate.getDay() << endl;

	cout << "Check out date: " << checkOutDate.getYear() << '-'
		<< setw(2) << checkOutDate.getMonth() << '-'
		<< setw(2) << checkOutDate.getDay() << endl;

	int count = 0;
	for (int i = 1; i < 6; ++i)
	{
		int r = availableRoomDatabase.compMinNumRooms(i, checkInDate, checkOutDate);
		if (r == 0)
			count++;
	}
	if (count == 5)
	{
		cout << "There are no rooms available!" << endl;
		cin.ignore();
		return;
	}
	else
		availableRoomDatabase.displayAvailableRooms(checkInDate, checkOutDate);

	const char roomTypeName[6][20] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room","Superior Suite", "Deluxe Suite" };

	int roomType = 0;
	int numRooms = 0;

	int choice[7] = { 0 };
	bool exit = false;
	while (true)
	{
		cout << "\nSelect Room type:" << endl;
		for (int i = 1; i < 6; ++i)
		{
			int r = availableRoomDatabase.compMinNumRooms(i, checkInDate, checkOutDate);		
			if (r != 0)
			{
				cout << i << " . " << roomTypeName[i] << endl;
				choice[i]++;
			}	
		}
		cout << "6 . Give up" << endl;
		cout << "?";
		cin >> roomType;

		if (roomType == 6)
		{
			cin.ignore();
			return;
		}
		else if (choice[roomType] == 0)
			continue;
		else
			break;
	}

	while (true)
	{
		int min_room = availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate);
		cout << "Number of rooms ( " << min_room << " rooms available ): ";
		cin >> numRooms;
		
		if (numRooms > min_room)
			continue;
		else
			break;
	}

	availableRoomDatabase.decreaseAvailRooms(roomType, numRooms, checkInDate, checkOutDate);

	cout << "\nID Number: ";
	string idNumber;
	cin >> idNumber;

	cout << "\nName: ";
	string name;
	cin >> name;

	cout << "\nMobile Phone: ";
	string mobile;
	cin >> mobile;
	cin.ignore();

	newReservation.setReservation(roomType, numRooms, checkInDate, checkOutDate, idNumber, name, mobile);

	cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
	newReservation.displayReservation();

	reservationDatabase.pushBack(newReservation);

	cout << "\nReservation successfully!" << endl;
}

void MakeReservation::computeAvailableMonths(Date currentDate, Date availableMonths[])
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int cur_year = currentDate.getYear();
	int cur_month = currentDate.getMonth();
	int cur_days = currentDate.getDay();


	for (int i = 0; i < 6; ++i)
	{
		if (cur_month + i > 12)
		{
			int t = (cur_month + i) % 12;
			availableMonths[i + 1].setYear(cur_year + 1);
			availableMonths[i + 1].setMonth(t);
			if (t == 2 && leapYear(cur_year + 1))
				availableMonths[i + 1].setDay(29);
			else
				availableMonths[i + 1].setDay(days[t]);
		}
		else
		{
			availableMonths[i + 1].setYear(cur_year);
			availableMonths[i + 1].setMonth(cur_month + i);
			if (cur_month + i == 2 && leapYear(cur_year))
				availableMonths[i + 1].setDay(29);
			else
				availableMonths[i + 1].setDay(days[cur_month + i]);
		}
	}
}

void MakeReservation::inputCheckInDates(Date& checkInDate, Date currentDate,
	Date availableMonths[], int& checkInYMCode, int& firstDay, int& lastDay)
{
	cout << "Please Input Check In Date" << endl;
	cout << endl;
	for (int i = 1; i < 7; ++i)
	{
		cout << i << ". " << availableMonths[i].getYear() << '-' << setw(2) << setfill('0') << availableMonths[i].getMonth() << endl;
	}

	while (true)
	{
		int num;
		cout << "?";
		cin >> num; //選擇月份

		if (num > 6 || num == 0) //防止輸入錯誤
			continue;

		checkInYMCode = num;
		firstDay, lastDay = 0;
		int days = 0; //選擇入住天數
		while (true)
		{
			if (num == 1)
			{
				firstDay = currentDate.getDay();
				lastDay = availableMonths[num].getDay();
			}
			else if (num == 6)
			{
				firstDay = 1;
				lastDay = availableMonths[num].getDay() - 1;
			}
			else
			{
				firstDay = 1;
				lastDay = availableMonths[num].getDay();
			}
			cout << "\nDay " << "(" << firstDay << " ~ " << lastDay << ")" << ":";

			cin >> days;
			if (days < firstDay || days > lastDay)
				continue;
			else
				break;
		}

		checkInDate.setYear(availableMonths[num].getYear());
		checkInDate.setMonth(availableMonths[num].getMonth());
		checkInDate.setDay(days);
		break;
	}
}

void MakeReservation::inputCheckOutDates(Date& checkOutDate, Date checkInDate,
	Date availableMonths[], int checkInYMCode, int firstDay, int lastDay)
{
	cout << "Please Input Check Out Date" << endl;
	cout << endl;

	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int InMonth = checkInDate.getMonth();
	int InDays = checkInDate.getDay();
	bool flag = false;
	if (InDays == days[InMonth])
	{
		if (leapYear(checkInDate.getYear()) && InMonth == 2);
		else
			flag = true;
	}

	int tmpCode = checkInYMCode;
	if (flag == true)
		tmpCode++;

	for (int i = tmpCode; i < 7; ++i)
			cout << i << ". " << availableMonths[i].getYear() << '-' << setw(2) << setfill('0') << availableMonths[i].getMonth() << endl;

	while (true)
	{
		int num;
		cout << "?";
		cin >> num; //選擇月份

		if (num > 6 || num < checkInYMCode) //防止輸入錯誤
			continue;

		firstDay, lastDay = 0; //存最一個月的第一天和最後一天
		int days = 0; //選擇入住天數

		while (true)
		{
			if (num == checkInYMCode)
			{
				firstDay = checkInDate.getDay() + 1;
				lastDay = availableMonths[num].getDay();
			}
			else
			{
				firstDay = 1;
				lastDay = availableMonths[num].getDay();
			}
			cout << "\nDay " << "(" << firstDay << " ~ " << lastDay << ")" << ":";
			cin >> days;
			if (days < firstDay || days > lastDay)
				continue;
			else
				break;
		}
		checkOutDate.setYear(availableMonths[num].getYear());
		checkOutDate.setMonth(availableMonths[num].getMonth());
		checkOutDate.setDay(days);
		break;
	}
}