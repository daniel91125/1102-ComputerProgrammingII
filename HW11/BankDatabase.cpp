// BankDatabase.cpp
// Member-function definitions for class BankDatabase.
#include <iostream>
#include <fstream>
#include "BankDatabase.h" // BankDatabase class definition

// BankDatabase default constructor initializes accounts
// read account informations for all accounts from the binary file "Accounts.dat"
BankDatabase::BankDatabase()
{
	ifstream inFile("Accounts.dat", ios::in | ios::binary);

	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	inFile.seekg(0, ios::beg);

	while (!inFile.eof())
	{
		Account tmp;
		inFile.read(reinterpret_cast<char*>(&tmp), sizeof(Account));
		accounts.push_back(tmp);
	}

}

// write account informations for all accounts to the binary file "Accounts.dat"
BankDatabase::~BankDatabase()
{
	ofstream inFile("Accounts.dat", ios::out | ios::binary);
	
	if (!inFile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < accounts.size(); ++i)
	{
		inFile.write(reinterpret_cast<char*>(&accounts[i]), sizeof(Account));
	}

	inFile.close();
}

// retrieve Account object containing specified account number
Account* BankDatabase::getAccount(int accountNumber)
{
	Account* tmpPtr;
	
	for (int i = 0; i < accounts.size(); ++i)
	{
		if (accounts[i].getAccountNumber() == accountNumber)
		{
			tmpPtr = &accounts[i];
			return tmpPtr;
		}
	}

	return nullptr; // if no matching account was found, return nullptr
}

// determine whether user-specified account number and PIN match
// those of an account in the database
bool BankDatabase::authenticateUser(int userAccountNumber, int userPIN)
{
	// attempt to retrieve the account with the account number
	Account* const userAccountPtr = getAccount(userAccountNumber);

	// if account exists, return result of Account function validatePIN
	if (userAccountPtr != nullptr)
		return userAccountPtr->validatePIN(userPIN);
	else
		return false; // account number not found, so return false
}

// return available balance of Account with specified account number
double BankDatabase::getAvailableBalance(int userAccountNumber)
{
	Account* const userAccountPtr = getAccount(userAccountNumber);
	return userAccountPtr->getAvailableBalance();
}

// return total balance of Account with specified account number
double BankDatabase::getTotalBalance(int userAccountNumber)
{
	Account* const userAccountPtr = getAccount(userAccountNumber);
	return userAccountPtr->getTotalBalance();
}

// credit an amount to Account with specified account number
void BankDatabase::credit(int userAccountNumber, double amount)
{
	Account* const userAccountPtr = getAccount(userAccountNumber);
	userAccountPtr->credit(amount);
}

// debit an amount from Account with specified account number
void BankDatabase::debit(int userAccountNumber, double amount)
{
	Account* const userAccountPtr = getAccount(userAccountNumber);
	userAccountPtr->debit(amount);
}