#pragma once
#include<string>
#include<iostream>
using namespace std;

class Account
{
public:
	Account(string, double, double);
	void view_balance();
	void withDraw(int);
	int  option_cost(int);
	void deposit(double);
	void exit();
	double totalbal();
private:
	string accName;
	double available;
	double total;
};

Account::Account(string accNum, double a_bal, double t_bal)
{
	accName = accNum;
	available = a_bal;
	total = t_bal;
}

void Account::view_balance()
{
	cout << "Balance Information: " << endl;
	cout << " - Available balance: " << available << endl;
	cout << " - Total balance: " << total << endl;
}

void Account::withDraw(int cost)
{
	available -= cost;
	total -= cost;
}

int Account::option_cost(int option)
{
	int withDraw_money = 0;

	switch (option)
	{
	case 1:
		withDraw_money = 20;
		break;
	case 2:
		withDraw_money = 40;
		break;
	case 3:
		withDraw_money = 60;	
		break;
	case 4:
		withDraw_money = 100;
		break;
	case 5:
		withDraw_money = 200;
		break;
	case 6:
		break;
	}

	return withDraw_money;
}


void Account::deposit(double money)
{
	money /= 100;
	total += money;
}

void Account::exit()
{
	cout << "Exiting the system..." << endl;
	cout << "Thank you! Goodbye!\n";
	cout << endl;
}

double Account::totalbal()
{
	return total;
}