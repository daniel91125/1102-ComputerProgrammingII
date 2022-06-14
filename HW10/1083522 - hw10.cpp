#include<iostream>
#include<string>
#include "Account.h";
using namespace std;

int main()
{
	Account acc1("12345", 1000.0, 1200.0);
	Account acc2("98765", 200.0, 200.0);

	string accNum;
	string password;
	int option = 0;
	while (1)
	{
		bool action = false;
		bool acc = true;
		cout << "Welcome!" << endl;
		cout << "\nPlease enter your account number: ";
		cin >> accNum;
		if (accNum == "12345")
		{
			cout << "\nEnter your PIN: ";
			cin >> password;
			if (password != "54321")
				cout << "\nWrong Password!!!" << endl;
			else
			{
				acc = true;
				action = true;
			}
			cout << endl;
		}
		else if (accNum == "98765")
		{
			cout << "\nEnter your PIN: ";
			cin >> password;
			if (password != "56789")
				cout << "\nWrong Password!!!" << endl;
			else
			{
				acc = false;
				action = true;
			}
			cout << endl;
		}
		else
			cout << endl;

		while (action)
		{
			cout << "Main menu:\n1 - View my balance\n2 - Withdraw cast\n3 - Deposit funds\n4 - Exit\n";
			cout << "Enter a choice: ";
			cin >> option;
			cout << endl;

			switch (option) {
			case 1:
				if (acc)
					acc1.view_balance();
				else
					acc2.view_balance();
				break;
			case 2:
				while (1)
				{
					int option;
					cout << "Withdrawl option:" << endl;
					cout << "1 - $20\n2 - $40\n3 - $60\n4 - $120\n5 - $200\n6 - Cancel transaction" << endl;
					cout << "\nChoose a withdrawal option (1-6): ";
					cin >> option;
					if (acc)
					{
						if (acc1.option_cost(option) > acc1.totalbal())
							cout << "\nYou should choose a small option!!!" << endl;
						else
						{
							acc1.withDraw(acc1.option_cost(option));
							break;
						}
					}
					else
					{
						if (acc2.option_cost(option) > acc2.totalbal())
							cout << "\nYou should choose a small option!!!" << endl;
						else
						{
							acc2.withDraw(acc2.option_cost(option));
							break;
						}
					}
					cout << endl;
				}
				cout << "\nPlease take your cash from the cash dispenser" << endl;
				cout << endl;
				break;
			case 3:
				double money;
				cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
				cin >> money;
				if (money != 0)
				{
					if (acc)
						acc1.deposit(money);
					else
						acc2.deposit(money);
					cout << "Please insert a deposit envelope containing $10.00 in the deposit slot." << endl;
					cout << "\nYour envelope has been received.\nNOTE: The money deposited will not be available until we verify the amount of any enclosed cash, and any enclosed checks clear." << endl;
				}
				cout << endl;
				break;
			case 4:
				if (acc)
					acc1.exit();
				else
					acc2.exit();
				action = false;
				break;
			}
		}
	}

}