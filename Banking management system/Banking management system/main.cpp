#include "Account.h"

void writeAccount();
void displayAccount(int display);
void modifyAccount(int modify);
void deleteAccount(int del);
void displayAll();
void depositWithdraw(int dep, int draw);
void intro();

int main() {
	int choice;
	int number;
	intro();

	do
	{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. NEW ACCOUNT";
		cout << "\n\n\t02. DEPOSIT AMOUNT";
		cout << "\n\n\t03. WITHDRAW AMOUNT";
		cout << "\n\n\t04. BALANCE ENQUIRY";
		cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout << "\n\n\t06. CLOSE AN ACCOUNT";
		cout << "\n\n\t07. MODIFY AN ACCOUNT";
		cout << "\n\n\t08. EXIT";
		cout << "\n\n\tSelect Your Option (1-8) ";
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
			writeAccount();
			break;
		case 2:
			cout << "Enter the account number: "; cin >> number;
			depositWithdraw(number, 1);
			break;
		case 3:
			cout << "Enter the account number: "; cin >> number;
			depositWithdraw(number, 2);
			break;
		case 4:
			cout << "Enter the account number: "; cin >> number;
			displayAccount(number);
			break;
		case 5:
			displayAll();
			break;
		case 6:
			cout << "Enter the account number: "; cin >> number;
			deleteAccount(number);
			break;
		case 7:
			cout << "Enter the account number: "; cin >> number;
			modifyAccount(number);
			break;
		case 8:
			cout << "Thank you";
			break;
		default:
			cout << "\a";
			break;
		}
		cin.ignore();
		cin.get();
	} while (choice != 8);
}

void writeAccount()
{
	Account account;
	ofstream file("account.txt", ios::binary | ios::app);
	account.createAccount();
	file.write(reinterpret_cast<char*> (&account), sizeof(account));
	file.close();
}

void displayAccount(int display)
{
	Account account;
	bool flag = false;
	ifstream file("account.txt", ios::binary);
	if (!file)
		cout << "Error" << endl;
	cout << "\nBalance details\n";
	while (file.read(reinterpret_cast<char*> (&account), sizeof(account))) {
		if (account.getAccountNumber() == display) {
			account.showAccount();
			flag = true;
		}
	}
	file.close();
	if (!flag)
		cout << "Error" << endl;
}

void modifyAccount(int number)
{
	bool found = false;
	Account account;
	fstream file("account.txt", ios::binary|ios::in|ios::out);
	if (!file)
		cout << "Error";
	while (!ws(file).eof() && found == false) {
		file.read(reinterpret_cast<char*>(&account), sizeof(account));
		if (account.getAccountNumber() == number) {
			account.showAccount();
			cout << "Enter the new details of the account: " << endl;
			account.modify();
			file.seekp(-1 * streamoff(sizeof(account)), ios::cur);
			file.write(reinterpret_cast<char*>(&account), sizeof(account));
			cout << "Record updated" << endl;
			found = true;
		}
	}
	file.close();
	if (found == false)
		cout << "Record not found" << endl;

}

void deleteAccount(int number)
{
	Account account;
	ifstream inFile("account.txt", ios::binary);
	if (inFile.fail())
		cout << "Error\n";
	ofstream outFile("temp.txt", ios::binary);

	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&account), sizeof(account))) {
		if (account.getAccountNumber() != number)
			outFile.write(reinterpret_cast<char*>(&account), sizeof(account));
	}
	inFile.close();
	outFile.close();
	remove("account.txt");
	rename("temp.txt", "account.txt");
	cout << "Record deleted\n";
}

void displayAll()
{
	Account account;
	ifstream file("account.txt", ios::binary);
	if (file.fail())
		cout << "Error\n";
	cout << "\n\t\tAccount holder list \n";
	cout << "\n========================================\n";
	cout << "Account Number \t\t Name \t\t Type \t\t Balance\n";
	cout << "\n========================================\n";
	while (file.read(reinterpret_cast<char*>(&account), sizeof(account)))
		account.report();
	file.close();

}

void depositWithdraw(int number, int option)
{
	int amount;
	bool found = false;
	Account account;
	fstream file("account.txt", ios::binary | ios::in | ios::out);
	if (file.fail())
		cout << "Error\n";
	while (!ws(file).eof() && found == false) {
		file.read(reinterpret_cast<char*> (&account), sizeof(account));
		if (account.getAccountNumber() == number) {
			account.showAccount();
			if (option == 1) {
				cout << "Enter amount to deposit: ";
				cin >> amount;
				account.addDeposit(amount);
			}
			if (option == 2) {
				cout << "Enter amount to withdraw: ";
				cin >> amount;
				int balance = account.getDeposit() - amount;
				if ((balance < 500 && account.getType() == 'S') || (balance < 10000 && account.getType() == 'C'))
					cout << "Insuffisant balance\n";
				else
					account.withdrawDeposit(amount);
			}
			file.seekp(-1 * streamoff(sizeof(account)), ios::cur);
			file.write(reinterpret_cast<char*> (&account), sizeof(account));
			cout << "Record updated\n";
			found = true;
		}
	}
	file.close();
	if (found == false)
		cout << "Record not found\n";
}

void intro()
{
	cout << "\n\n\n\t  BANK AUDI";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\t  SYSTEM";
	cin.get();
}
