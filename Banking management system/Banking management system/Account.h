#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;
class Account
{
public:
	Account();
	~Account();

	void createAccount();
	void showAccount() const;
	void modify();
	void addDeposit(int dep);
	void withdrawDeposit(int draw);
	void report() const;
	int getAccountNumber() const;
	int getDeposit() const;
	char getType() const;

private:
	int accountNumber, deposit;
	char type;
	char name[50];
};

#endif ACCOUNT