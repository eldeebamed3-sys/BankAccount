//Update On Bank Account
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <fstream>
using namespace std;
const string ClientsFileName = "Clients.txt";

//void ShowMainMeune();
void ShowTransactionMainMenue();

struct sClient
{
	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	double AccountBalance = 0;
	bool MarkOfDelete = false;
};

vector<string>SplitString(string S1, string Delim)
{
	vector<string>vString;
	short Pos = 0;
	string sWord;

	while ((Pos = (short)S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, Pos);
		if (sWord != " ")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, Pos + Delim.length());
	}
	if (S1 != " ")
	{
		vString.push_back(S1);
	}

	return vString;
}

sClient ConvertLineOfRecord(string Line, string Sperator = " - ")
{
	sClient Client;
	vector <string>vClientData;
	vClientData = SplitString(Line, Sperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.ClientName = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

string ConvertRecordOfLine(sClient Client, string Sperator = " - ")
{
	string Line;

	Line += Client.AccountNumber + Sperator;
	Line += Client.PinCode + Sperator;
	Line += Client.ClientName + Sperator;
	Line += Client.Phone + Sperator;
	Line += to_string(Client.AccountBalance);

	return Line;
}

vector<sClient>LoadClientDataFromFile(string FileName)
{
	vector<sClient>vClient;
	fstream MyFile;

	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineOfRecord(Line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}

bool ClientExistClientByAccountNumber(string AccountNumber, sClient& Client)
{
	vector<sClient>vClient = LoadClientDataFromFile(ClientsFileName);

	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

sClient ReadClientData()
{
	sClient Client;

	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	sClient TempClient;
	while (ClientExistClientByAccountNumber(Client.AccountNumber, TempClient))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin, Client.AccountNumber);
	}

	cout << "Enter Pin Code? ";
	getline(cin, Client.PinCode);

	cout << "Enter Client Name? ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance? ";
	cin >> Client.AccountBalance;

	return Client;
}
//_______________________________________________________________

void AddClientsDataOfFile(string FileName, string ClientsLine)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << ClientsLine << endl;
		MyFile.close();
	}
}
void AddNewClients()
{
	sClient Client;

	Client = ReadClientData();
	AddClientsDataOfFile(ClientsFileName, ConvertRecordOfLine(Client));
}
void AddClients()
{
	char AddMore = 'Y';
	do
	{
		system("cls");
		cout << "\n-------------------------------------------------" << endl;
		cout << "\t Add New Clients Screen " << endl;
		cout << "-------------------------------------------------" << endl;

		cout << "Adding New Client:\n\n";
		AddNewClients();

		cout << "\nClient Added Successfully, do you want to add Add more clients? Y/N?";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

//-----------------Show Client Data----------------------------------------
void PrintClientData(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.ClientName;
	cout << "| " << setw(15) << left << Client.Phone;
	cout << "| " << setw(10) << left << Client.AccountBalance;
}

void ShowClientList(vector<sClient>vClient)
{
	cout << "\n\t\t\t\t\t Client List (" << vClient.size() << ") Client(s)." << endl;

	cout << "__________________________________________________________";
	cout << "__________________________________________________________\n" << endl;;
	cout << "| " << setw(15) << right << "Account Number ";
	cout << "| " << setw(10) << left << "Pin Code ";
	cout << "| " << setw(40) << left << "Client Name ";
	cout << "| " << setw(15) << left << "Phone ";
	cout << "| " << setw(15) << left << "Balance ";
	cout << "\n__________________________________________________________";
	cout << "__________________________________________________________\n" << endl;
	
	if (vClient.size() == 0)
		cout << "\t\t\tNo Clients Aveilable In The System!";
	else
	
	for (sClient& Client : vClient)
	{
		PrintClientData(Client);
		cout << endl;
	}
	cout << "\n__________________________________________________________";
	cout << "__________________________________________________________\n" << endl;
}
//---------------------------------------------------------

void PrintDataClientOfLine(sClient Client)
{
	cout << "\nThe following are the client details: " << endl;
	cout << "--------------------------------------\n";
	cout << "Account Number : " << Client.AccountNumber;
	cout << "\nPin Code       : " << Client.PinCode;
	cout << "\nClient Name    : " << Client.ClientName;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n--------------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient>vClient, sClient& Client)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool MarkOfDeleteClientFromFile(string AccountNumber, vector<sClient>& vClient)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkOfDelete = true;
			return true;
		}
	}
	return false;
}

vector<sClient>SaveClientDataFromFile(string FileName, vector<sClient>& vClient)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClient)
		{
			if (C.MarkOfDelete == false)
			{
				DataLine = ConvertRecordOfLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\n-------------------------------------------------" << endl;
		cout << "\t Delete Client Screen " << endl;
		cout << "-------------------------------------------------" << endl;
		PrintDataClientOfLine(Client);

		cout << "\n\nAre you want to delete this client? Y/N? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			MarkOfDeleteClientFromFile(AccountNumber, vClient);
			SaveClientDataFromFile(ClientsFileName, vClient);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
		return false;
	}

	return false;
}

//----------------Update-----------------------------------------
sClient ChanageClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;

	cout << "\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.ClientName);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintDataClientOfLine(Client);

		cout << "\n\nAre you want to Update this client? Y/N? ";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChanageClientRecord(AccountNumber);
					break;
				}
			}

			SaveClientDataFromFile(ClientsFileName, vClient);
			cout << "\n\nClient Update Successfully.\n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n";
		return false;
	}
};

//-----------------------------------------------------------------

void displayTotalBalance(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.ClientName;
	cout << "| " << setw(15) << left << Client.AccountBalance;
}

void ShowTotalBalanceOfClients(vector<sClient>vClient)
{
	sClient Client;
	
	cout << "\t\t\t\t\t Balance List (" << vClient.size() << ") Clients(s).\n";
	cout << "__________________________________________________________";
	cout << "__________________________________________________________\n" << endl;;
	cout << "| " << setw(15) << left << "Account Number ";
	cout << "| " << setw(40) << left << "Client Name ";
	cout << "| " << setw(15) << left << "Balance ";
	cout << "\n__________________________________________________________";
	cout << "__________________________________________________________\n" << endl;
	double TotalBalance = 0;

	if (vClient.size() == 0)
		cout << "\t\t\t No Clients Available In The System!";

	else

	for (sClient& Client : vClient)
	{
		displayTotalBalance(Client);
		TotalBalance += Client.AccountBalance;
		cout << endl;
	}
	cout << "\n__________________________________________________________";
	cout << "__________________________________________________________\n" << endl;

	cout << "\t\t\t\t\t Total Balances = " << TotalBalance << endl;
}

bool DepositClientByAccountNumber(string AccountNumber, vector<sClient>& vClient, double Amount)
{
	sClient Client;
	char Answer = 'n';

	cout << "\nAre you sure you want perfrom this transactions? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		for (sClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientDataFromFile(ClientsFileName, vClient);
				cout << "\n\nDone Successfully. New Balance is " << C.AccountBalance;

				return true;
			}
		}
		return false;
	}
}

string ReadAccountNumber()
{
	string AccountNumber = " ";

	cout << "\nPlease enter Account Number? ";
	cin >> AccountNumber;

	return AccountNumber;
}

void ShowDepositScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\t\tDeposit Screen";
	cout << "\n------------------------------------------\n";

	sClient Client;
	vector<sClient>vClient = LoadClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] dose not exist.\n";
		AccountNumber = ReadAccountNumber();	
	}

	PrintDataClientOfLine(Client);
	
	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;

	DepositClientByAccountNumber(AccountNumber, vClient, Amount);
}

void ShowWithdrawScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\t\tWithdraw Screen";
	cout << "\n------------------------------------------\n";
	sClient Client;
	vector<sClient>vClient = LoadClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}

	PrintDataClientOfLine(Client);

	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;

	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "\nPlease enter onther Amount? ";
		cin >> Amount;
	}

	DepositClientByAccountNumber(AccountNumber, vClient, Amount * -1);
}
//-----------------------------------------------------------------
void ShowMainMenu()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\t Main Menue Screen           \n";
	cout << "=================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Exit.\n";
	cout << "=================================================\n";
}

void GoBackMainMenu()
{
	cout << "\n\nPress any to key to go back to Main Menue...";
	system("Pause>0");
}

void GoBackTransactionMenu()
{
	cout << "\n\nPress any to key to go back to Main Menue...";
	system("Pause>0");
    ShowTransactionMainMenue();
}

enum enTransactionsOption
{
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalance = 3,
	eMainMenu = 4
};

short ReadTransctionsMenueOption()
{
	short Option = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> Option;

	while (cin.fail() || Option < 1 || Option > 4)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter Number from [1 to 4]: ";
		cin >> Option;
	}
	return Option;
}

void PerformTransactionMenueOption(enTransactionsOption TransactionsOption)
{
	double Amount = 0;
	string AccountNumber;
	sClient Client;
	vector<sClient>vClient = LoadClientDataFromFile(ClientsFileName);

	switch (TransactionsOption)
	{
	case enTransactionsOption::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackTransactionMenu();
		break;
	}
	case enTransactionsOption::eWithdraw:
	{
		system("cls");
		ShowWithdrawScreen();
		GoBackTransactionMenu();
		break;
	}
	case enTransactionsOption::eTotalBalance:
	{
		system("cls");
		ShowTotalBalanceOfClients(vClient);
		GoBackTransactionMenu();
		break;
	}
	case enTransactionsOption::eMainMenu:
	{
		ShowMainMenu();
		break;
	}
	default:
	{
		cout << "\nInvalid Option";
		break;
	}

	}
}

void ShowTransactionMainMenue()
{
	system("cls");
	cout << "=================================================\n";
	cout << "\t\t Transactions Menue Screen           \n";
	cout << "=================================================\n";
	cout << "\t [1] Deposit.\n";
	cout << "\t [2] Withdraw.\n";
	cout << "\t [3] Total Balances.\n";
	cout << "\t [4] Main Menue.\n";
	cout << "=================================================\n";

	PerformTransactionMenueOption((enTransactionsOption)ReadTransctionsMenueOption());
}

void PerformMainMenuOption(short Choice)
{
	sClient Client;
	vector<sClient>vClient;
	string AccountNumber = " ";

	switch (Choice)
	{
	case 1:
	{
		system("cls");
		vClient = LoadClientDataFromFile(ClientsFileName);
		ShowClientList(vClient);
		GoBackMainMenu();
		break;
	}
	case 2:
	{
		system("cls");
		cout << "\n-------------------------------------------------" << endl;
		cout << "\t Add New Clients Screen " << endl;
		cout << "-------------------------------------------------" << endl;
		AddClients();
		GoBackMainMenu();
		break;
	}
	case 3:
	{
		system("cls");
		cout << "\n-------------------------------------------------" << endl;
		cout << "\t Delete Client Screen " << endl;
		cout << "-------------------------------------------------" << endl;
		vClient = LoadClientDataFromFile(ClientsFileName);
		AccountNumber = ReadAccountNumber();
		DeleteClientByAccountNumber(AccountNumber, vClient);
		GoBackMainMenu();
		break;
	}
	case 4:
	{
		system("cls");
		cout << "\n-------------------------------------------------" << endl;
		cout << "\t Delete Client Screen " << endl;
		cout << "-------------------------------------------------" << endl;
		vClient = LoadClientDataFromFile(ClientsFileName);
		AccountNumber = ReadAccountNumber();
		UpdateClientByAccountNumber(AccountNumber, vClient);
		GoBackMainMenu();
		break;
	}
	case 5:
	{
		system("cls");
		cout << "\n-------------------------------------------------" << endl;
		cout << "\t  Find Client Screen " << endl;
		cout << "-------------------------------------------------" << endl;
		AccountNumber = ReadAccountNumber();
		if (ClientExistClientByAccountNumber(AccountNumber, Client))
		{
			PrintDataClientOfLine(Client);
		}
		else
		{
			cout << "\nClient with Account Number (" << AccountNumber << ") Not Found!";
		}
		GoBackMainMenu();
		break;
	}
	case 6:
	{
		system("cls");
		ShowTransactionMainMenue();
		break;
	}
	case 7:
	{
		system("cls");
		cout << "\n--------------------------------------\n";
		cout << "\t Program Ends :-)";
		cout << "\n--------------------------------------\n";
		GoBackMainMenu();
		break;
	}
	default:
	
		cout << "Invalid Option!\n";
		break;
	}
}

void StartBack()
{
	short Choice = 0;
	do
	{
		ShowMainMenu();
		cout << "Choose what do you want to do? [1 to 7]? ";
		cin >> Choice;

		PerformMainMenuOption(Choice);

	} while (Choice != 7);
}

int main()
{
	StartBack();

	system("Pause>0");
	return 0;
}
