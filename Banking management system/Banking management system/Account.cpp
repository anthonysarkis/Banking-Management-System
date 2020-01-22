#include "Account.h"

Account::Account() : accountNumber(0), deposit(0), name("NUL"), type('N')
{
}

Account::~Account()
{
}

void Account::createAccount()
{
	cout << "Enter your account number: ";
	cin >> accountNumber;
	cout << "\nEnter your name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter the type of the account (C/S): ";
	cin >> type;
	type = toupper(type);
	cout << "\nHow much money would you like to deposit: ";
	cin >> deposit;
	cout << "\nThank you." << endl;
}

void Account::showAccount() const
{
	cout << "Account number: " << accountNumber << endl;
	cout << "Account holder name: " << name << endl;
	cout << "Type of account: " << type << endl;
	cout << "Balance amount: " << deposit << endl;
}

void Account::modify()
{
	cout << "Account number: " << accountNumber << endl;
	cout << "Modify account holder name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify type of account: ";
	cin >> type;
	type = toupper(type);
	cout << "\nModify balance amount: ";
	cin >> deposit;
	cout << endl;
}

void Account::addDeposit(int dep)
{
	deposit += dep;
}

void Account::withdrawDeposit(int draw)
{
	deposit -= draw;
}

void Account::report() const
{
	cout << accountNumber << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int Account::getAccountNumber() const
{
	return accountNumber;
}

int Account::getDeposit() const
{
	return deposit;
}

char Account::getType() const
{
	return type;
}
