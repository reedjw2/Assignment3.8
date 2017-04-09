// Assignment3.8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <ctime>

using namespace std;

/*struct date //set Date function
{
int m, d, y;
};*/

struct tm* timeinfo;

const char* MONTHS[] = {
	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December" };

class account
{
protected:
	unsigned int accountNumber;
	static unsigned int accountNumberCounter;
	tm creation;
	float rate;
	float bal;

public:
	virtual float monthlyInterest() = 0;
	virtual float orderChecks() = 0;

	account()
	{
		accountNumber = getAccountNumber();
		creation;
		rate = 0;
		bal = 0;
	}

	account(int a, float r, float b)
	{
		accountNumber = a;
		//creation = c;
		rate = r;
		bal = b;
	}

	void creationDate()
	{
		time_t     rawtime;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		cout << "Today's date is "
			<< timeinfo->tm_mday << " "
			<< MONTHS[timeinfo->tm_mon] << " "
			<< (timeinfo->tm_year + 1900) << ".\n";
	}

	tm getDate(tm d)
	{
		return d;
	}

	/*void setAccountNumber(unsigned int acno)
	{
	accountNumber = acno++;
	}*/

	int getAccountNumber()
	{
		accountNumber = accountNumberCounter;
		accountNumberCounter++;
		return accountNumber;
	}

	void setAccountRate(float r)
	{
		rate = r;
	}

	virtual float getAccountRate()
	{
		return rate;
	}

	void setBalance(float b)
	{
		bal = b;
	}

	float getBalance()
	{
		return bal;
	}

	virtual bool withdraw(float b)
	{
		if (bal < b)
			return -1;
		bal = bal - b;
		return 0;
	}

	virtual bool deposit(float d)
	{
		if (d < 0)
			return -1;
		bal = bal + d;
		return 0;
	}

	virtual void display()
	{
		cout << "Account Number:" << accountNumber << endl;
		cout << "Interest Rate:" << rate << endl;
		cout << "Balance:" << bal << endl;
	}
};

unsigned int account::accountNumberCounter = 1;

class Savings :public account
{
public:
	Savings(int a, float r, float b) : account(a, r, b)
	{

	}
	float orderChecks()
	{
		return 0;
	}

	void setRate()
	{
		float bal = getBalance();
		if (bal < 10000)
		{
			account::setAccountRate(1);
		}
		else
		{
			account::setAccountRate(2);
		}
	}

	void setBalance(float b, float r)
	{
		account::setBalance(b);
		setAccountRate(r);
	}

	bool withdraw(float b)
	{
		bool  c = account::withdraw(b);
		b = account::withdraw(2);
		return b;
	}

	bool deposit(float d)
	{
		bool c = account::deposit(d);
		return d;
	}

	float monthlyInterest()
	{
		if (bal < 10000)
		{
			rate = (1 + .01 / 12);
			bal = bal * rate;
			return rate;
		}
		if (bal >= 10000)
		{
			rate = (1 + .02 / 12);
			bal = bal * rate;
			return rate;
		};
	}
};

class Checking :public account
{
public:
	Checking(int a, float r, float b) : account(a, r, b)
	{
	}

	void setBalance(float b)
	{
		account::setBalance(b);
	}

	void setRate()
	{
		account::setAccountRate(0);
	}

	bool withdraw(float b)
	{
		if (account::withdraw(b))
		{
			if (getBalance() < b)
				return account::withdraw(b);
		}
		return -1;
	}
	bool deposit(float d)
	{
		bool c = account::deposit(d);
		return d;
	}
	float orderChecks()
	{
		bal = bal - 15;
		return bal;
	}
	float monthlyInterest()
	{
		return rate;
	}
};

class CD :public account
{
	int term;
public:
	CD(int a, float r, float b, int t) :account(a, r, b)
	{
		term = t;
		update();
	}

	float orderChecks()
	{
		return 0;
	}

	void update()
	{
		if (term < 5)
		{
			account::setAccountRate(5);
		}
		else
		{
			account::setAccountRate(10);
		}
	}

	bool withdraw(float b)
	{

		float w = 10 * getBalance() / 100;
		account::withdraw(w);
		return account::withdraw(b);
	}

	bool deposit(float d)
	{
		bool c = account::deposit(d);
		return d;
	}

	float getBalance()
	{
		return bal;
	}

	float monthlyInterest()
	{
		return 0;
	}
};

int main()
{
	account * ac1;
	account * ac2;
	account * ac3;

	ac1 = new Savings(100, 0, 0);
	ac3 = new CD(101, 0, 0, 3);
	ac2 = new Checking(102, 0, 0);

	//create and deposit each account
	ac1->deposit(10000);
	ac2->deposit(600);
	ac3->deposit(10000);
	cout << "Display Savings Account: " << endl;
	ac1->display();
	cout << "Display Checking Account: " << endl;
	ac2->display();
	cout << "Display CD Account: " << endl;
	ac3->display();

	//monthly interest for savings and CD
	cout << "\n\n--------\n";
	cout << "Savings Interest: " << endl;
	ac1->monthlyInterest();
	ac3->monthlyInterest();
	ac1->display();
	cout << "CD interest" << endl;
	ac3->display();

	//order checks
	cout << "\n\n--------\n";
	cout << "Order Checks: " << endl;
	ac2->orderChecks();
	ac2->display();

	//withdraw Savings and Checking accounts
	cout << "\n\n--------\n";
	cout << "Checkings withdrawal" << endl;
	ac2->withdraw(200);
	ac1->withdraw(1000);
	ac2->display();
	cout << "Savings Withdrawal:" << endl;
	ac1->display();

	//early withdraw of CD
	cout << "\n" << endl;
	cout << "Withdraw CD:" << endl;
	ac3->withdraw(2000);
	ac3->display();
	cout << "\n" << endl;

	return 0;

}