

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
const string clientFile = "Clients.txt";
void showMainMenue();
void showTransactionsMenueScreen();
enum enMainMenueOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransactions = 6,
	eExit = 7
};
enum enTransactionMenueOptions
{
	eDeposite = 1, eWithdraw = 2,
	eTotalBalances = 3, eMainMenue=4
};
struct stClient
{
	string acountNumber;
	string pinCode;
	string name;
	string phone;
	string acountBalance;
	bool mark = false;

};
short readTransactionsMenueOption() {
	short choice = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> choice;
	return choice;
}
short readMainMenueOption() {
	short choice = 0;
	cout << "Choose what do you want to do? [1 to 7]? ";
	cin >> choice;
	return choice;
}
vector<string> splitString(string line, string separator = "#//#") {
	short pos = 0;
	string word; 
	vector<string> vString;
	while ((pos = line.find(separator))!=std::string::npos) {
		word = line.substr(0,pos);
		if (word!="")
		{
			vString.push_back(word);
			

		}
		line.erase(0, pos + separator.length());
	}
	if (line != "")
	{
		vString.push_back(line);

	}
	return vString;
}
stClient convertLineToRecord(string line) {
	stClient client;
	vector<string> vString = splitString(line);
	client.acountNumber = vString[0];
	client.pinCode = vString[1];
	client.name = vString[2];
	client.phone = vString[3];
	client.acountBalance = vString[4];
	return client;

	

}
vector<stClient> loadDataFromFile(string fileName) {
	vector<stClient> vClient;
	fstream myFile;
	myFile.open(fileName, ios::in);
	if (myFile.is_open())
	{
		string line;
		stClient client;
		while (getline(myFile,line)) {
			client = convertLineToRecord(line);
			vClient.push_back(client);
		}
		myFile.close();

	}
	return vClient;
}
void printClientRecordLine(stClient client) {
	cout << '|' << setw(15) << client.acountNumber << setw(2) << '|' << setw(15) << client.pinCode << setw(2) << '|' << setw(15) << client.name << setw(15) << '|' << setw(10) << client.phone << setw(10) << '|' << setw(10) <<client.acountBalance;
}
void showClientsList() {
	vector<stClient> vClient;
	vClient = loadDataFromFile(clientFile);
	cout << "\t\tClient List (" << vClient.size() << ") Client(s)\n";
	cout << "----------------------------------------------------------------------------------------------------------------\n";
	cout << '|' << setw(15) << "Acount Number" << setw(2) << '|' << setw(15) << "Pin Code" << setw(2) << '|' << setw(15) << "Client Name" << setw(15) << '|' << setw(10) << "Phone" << setw(10) << '|' << setw(10) << "Balance\n";
	cout << "----------------------------------------------------------------------------------------------------------------\n";
	for (stClient client:vClient) {
		printClientRecordLine(client);
		cout << endl;

}
	cout << "----------------------------------------------------------------------------------------------------------------\n";
}
void goBackToTransactionsMenue() {
	cout << "Press any key to go back to Transactions Menue...";
	system("pause>0");
	showTransactionsMenueScreen();
}
void goBackToMainMenue() {
	cout << "Press any key to go back to Main Menue...";
	system("pause>0");
	showMainMenue();
}
bool clientExistByAcountNumber(stClient client,string fileName) {
	fstream myFile;
	myFile.open(fileName,ios::in);
	if (myFile.is_open())
	{
		string line;
		stClient sClient;
		while (getline(myFile,line)) {
			sClient = convertLineToRecord(line);
			if (sClient.acountNumber==client.acountNumber)
			{
				myFile.close();
				return true;

			}
		}
		myFile.close();
	}
	return false;
}
stClient readNewClient() {
	stClient client;
	cout << "Enter Acount Number? ";
	cin >> client.acountNumber;
	while (clientExistByAcountNumber(client, clientFile)) {
		cout << "\nClient with Acoutn Number " << client.acountNumber << " Already Exist Please Enter Another Acount Number. ";
		cin >> client.acountNumber;
	}
	cout << "Please Enter Pin Code: ";
	cin >> client.pinCode;
	cout << "Please Enter Name: ";
	cin >> client.name;
	cout << "Please Enter Phone Number:  ";
	cin >> client.phone;
	cout << "Please Enter Acount Balance: ";
	cin >> client.acountBalance;
	return client;
}
string convertRecordToLine(stClient client) {
	string line;
	line = client.acountNumber + "#//#";
	line += client.pinCode + "#//#";
	line += client.name + "#//#";
	line += client.phone + "#//#";
	line += client.acountBalance;
	return line;

}
void addDataLineToFile(string fileName, string line) {
	fstream myFile;
	myFile.open(fileName, ios::out | ios::app);
	if (myFile.is_open())
	{
		myFile << line << endl;

	}
	myFile.close();
}
void addNewClient() {
	stClient client;
	client = readNewClient();
	addDataLineToFile(clientFile,convertRecordToLine(client));
	
}
void addNewClients() {
	char add = 'n';
	do
	{
		cout << "Adding New Client\n";
		addNewClient();

		cout << "\nDo you want to add more clients? [Y/N]? ";
		cin >> add;

	} while (toupper(add)=='Y');

}
void showAddNewClientsScreen() {
	cout << "---------------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "---------------------------------------------\n";
	addNewClients();

}
string readAcountNumber() {
	string acountNumber;
	cout << "Please Enter Acount Number? ";
	cin >> acountNumber;
	return acountNumber;
}
bool findClientByAcountNumber(vector<stClient> vClient,string acountNumber,stClient& client) {
	for (stClient sClient:vClient) {
		if (sClient.acountNumber==acountNumber)
		{
			client = sClient;
			return true;

		}
	}
	return false;
}
void printClientCard(stClient client) {
	cout << "The following are the client details:\n";
	cout << "---------------------------------------------\n";
	cout << "Acount Number: " << client.acountNumber << endl;
	cout << "Pin Code: " << client.pinCode << endl;
	cout << "Name: " << client.name << endl;
	cout << "Phone: " << client.phone << endl;
	cout << "Acount Balance: " << stod(client.acountBalance) << endl;
	cout << "---------------------------------------------\n\n";


}
void markClientToDelete(string acountNumber, vector<stClient>& vClient) {
	for (stClient& client:vClient)
	{
		if (client.acountNumber==acountNumber) {
			client.mark = true;
	}

	}
}
void saveDataToFile(string fileName, vector<stClient> vClient) {
	fstream myFile;
	myFile.open(fileName, ios::out);
	if (myFile.is_open())
	{
		string line;
		for (stClient client : vClient) {
			if (client.mark==false)
			{
				line = convertRecordToLine(client);
				myFile << line << endl;
			}
 }
		myFile.close();
	}
}
bool deleteClientByAcountNumber(vector<stClient>& vClient,string acountNumber) {
	stClient client;
	char answer = 'y';
	if (findClientByAcountNumber(vClient,acountNumber,client))
	{
		printClientCard(client);
		cout << "Are you sure you want to delete this client? [Y/N]?";
		cin >> answer;
		if (answer=='y'||answer=='Y')
		{
			markClientToDelete(acountNumber,vClient);
			saveDataToFile(clientFile, vClient);
			vClient = loadDataFromFile(clientFile);
			cout << "\nClient Deleted Successfully!\n";
			return true;

		}

	}
	return false;
}
void showDeleteClientScreen() {
	cout << "---------------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "---------------------------------------------\n";
	vector<stClient> vClient = loadDataFromFile(clientFile);
	string acountNumber = readAcountNumber();
	deleteClientByAcountNumber(vClient,acountNumber);
}
stClient changeClientRecord(string acountNumber) {
	stClient client;
	client.acountNumber = acountNumber;
	cout << "Please Enter Pin Code: ";
	cin >> client.pinCode;
	cout << "Please Enter Name: ";
	cin >> client.name;
	cout << "Please Enter Phone Number:  ";
	cin >> client.phone;
	cout << "Please Enter Acount Balance: ";
	cin >> client.acountBalance;
	return client;
}
void updateClientByAcountNumber(vector<stClient>& vClient, string acountNumber) {
	stClient client;
	char answer = 'y';
	if (findClientByAcountNumber(vClient, acountNumber, client))
	{
		printClientCard(client);
		cout << "Are you sure you want to update this client info? [Y/N]?";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (stClient& sClient:vClient) {
				if (sClient.acountNumber==acountNumber)
				{
				sClient=changeClientRecord(acountNumber);
				break;
				}
		}
			
			saveDataToFile(clientFile, vClient);
			cout << "\nClient Updated Successfully!\n";
			

		}

	}
	else
	{
		cout << "\nClient not found\n";
	}
	
}
void showUpdateClientInfoScreen() {
	cout << "---------------------------------------------\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "---------------------------------------------\n";
	vector<stClient> vClient = loadDataFromFile(clientFile);
	string acountNumber = readAcountNumber();
	updateClientByAcountNumber(vClient, acountNumber);
}
void showFindClientScreen() {
	cout << "---------------------------------------------\n";
	cout << "\tFind Client  Screen\n";
	cout << "---------------------------------------------\n";
	vector<stClient> vClient = loadDataFromFile(clientFile);
	string acountNumber = readAcountNumber();
	stClient client;
	if (findClientByAcountNumber(vClient, acountNumber, client))
	{
		printClientCard(client);
	}
}

void showExitScreen() {
	cout << "---------------------------------------------\n";
	cout << "\tExit  Screen\n";
	cout << "---------------------------------------------\n";
	cout << "\nEnd Of Program\n";
}
void performMainMenueOption(enMainMenueOptions mainMenueOptions) {
	switch (mainMenueOptions) {
	case eListClients:system("cls");
		showClientsList();
		goBackToMainMenue();
		break;
	case eAddNewClient:
		system("cls");
		showAddNewClientsScreen();
		goBackToMainMenue();
		break;
	case eDeleteClient:
		system("cls");
		showDeleteClientScreen();
		goBackToMainMenue();
		break;
	case eUpdateClient:
		system("cls");
		showUpdateClientInfoScreen();
		goBackToMainMenue();
		break;
	case eFindClient:
		system("cls");
		showFindClientScreen();
		goBackToMainMenue();
		break;
	case eTransactions:
		system("cls");
		showTransactionsMenueScreen();
		goBackToMainMenue();
		break;
	case eExit:
		system("cls");
		showExitScreen();
		goBackToMainMenue();
		break;
	}


}
stClient addDepositeAmount(string acountNumber) {
	double depositeAmount;
	stClient client;
	cout << "Please enter deposite amount?";
	cin >> depositeAmount;
	client.acountBalance += depositeAmount;
	return client;
}
void addingDepositeAmount(vector<stClient>& vClient,string acountNumber,stClient& client) {
	double depositeAmount;
	char answer;
	double acountBalance;
	cout << "\n\nPlease enter deposite amount?";
	cin >> depositeAmount;
	cout << "\n\n Are you sure you want to perform this transaction? [y/n]?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		for (stClient& sClient: vClient) {
			if (sClient.acountNumber==acountNumber)
			{
				acountBalance = stod(sClient.acountBalance);
				acountBalance += depositeAmount;
				sClient.acountBalance = to_string(acountBalance);
				client = sClient;
				break;

			}
	}

	}
}
void performDepositeToClient() {
	vector<stClient> vClient = loadDataFromFile(clientFile);
	string acountNumber = readAcountNumber();
	stClient client;
	double depositeAmount;
	if (findClientByAcountNumber(vClient,acountNumber,client))
	{
		printClientCard(client);
		addingDepositeAmount(vClient,acountNumber,client);
		saveDataToFile(clientFile,vClient);
		cout << "Deposite added successfully!\n\n";


	}
	

}
double calculateTotalBalance(vector<stClient> vClient) {
	double totalBalance = 0; 
	for (stClient client : vClient) {
		totalBalance += stod(client.acountBalance);
	}
	return totalBalance;
}
void showBalanceOfEachClient(vector<stClient> vClient) {
	double totalBalance = 0;
	cout << '|' << setw(15) << "Acount Number" <<  setw(2) << '|' << setw(20) << "Client Name" <<  setw(10) << '|' << setw(10) << "Balance\n";
	cout << "----------------------------------------------------------------------------------------------------------\n";

	for (stClient client:vClient) {
		cout << '|' << setw(15) << client.acountNumber << setw(2) << '|' << setw(20) << client.name << setw(10) << '|' << setw(10) << client.acountBalance<<endl;
	}
	cout << "----------------------------------------------------------------------------------------------------------\n";
	totalBalance = calculateTotalBalance(vClient);
	cout << "\t\t\t\tTotal Balances = " << totalBalance << endl<<endl<<endl;
}
void showTotalBalancesScreen() {
	vector<stClient> vClient = loadDataFromFile(clientFile);
	cout << "\t\t\t\t\tBalances List (" << vClient.size() << ") Client(s).\n";
	cout << "----------------------------------------------------------------------------------------------------------\n";
	showBalanceOfEachClient(vClient);

}
void showDepositeScreen() {
	cout << "---------------------------------------------\n";
	cout << "\t\tDeposite Screen\n";
	cout << "---------------------------------------------\n";
	performDepositeToClient();
}
void calculateBalanceAfterWithdraw(stClient& client , double amount) {
	double finalBalance;
	finalBalance = stod(client.acountBalance) - amount;
	client.acountBalance = to_string(finalBalance);
}
void checkTheAmountToWithdraw(vector<stClient>& vClient,string acountNumber) {
	double amount = 0;
	char answer;
	cout << "Please enter withdraw amount? ";
	cin >> amount;
	for(stClient& client:vClient){
		if(client.acountNumber==acountNumber){
			while (amount > stod(client.acountBalance)) {
				cout << "Amount Exceed the balance, you can withdraw up to " << client.acountBalance << endl;
				cout << "Please enter another amount? ";
				cin >> amount;
			}
			cout << "Are you sure you want to perform this transaction? [y/n]? ";
			cin >> answer;
			if (answer == 'Y' || answer == 'y')
			{
				calculateBalanceAfterWithdraw(client, amount);
				cout << "Withdraw is done successfully\n";
			}
			else
			{
				goBackToTransactionsMenue();
			}
		}
	}

}
void performWithdrawToClient() {
	vector<stClient> vClient = loadDataFromFile(clientFile);
	string acountNumber = readAcountNumber();
	stClient client;
	if (findClientByAcountNumber(vClient, acountNumber, client))
	{
		printClientCard(client);
		checkTheAmountToWithdraw(vClient,acountNumber);
		saveDataToFile(clientFile,vClient);
	}
}
void showWithdrawScreen() {
	cout << "---------------------------------------------\n";
	cout << "\t\Withdraw Screen\n";
	cout << "---------------------------------------------\n";
	performWithdrawToClient();
}
void performTransactionMenueOption(enTransactionMenueOptions transactionOptions) {
	switch (transactionOptions) {
	case eDeposite:system("cls");
		showDepositeScreen();
		goBackToTransactionsMenue();
		break;
	case eWithdraw:system("cls");
		showWithdrawScreen();
		goBackToTransactionsMenue();
		break;
	case eTotalBalances:system("cls");
		showTotalBalancesScreen();
		goBackToTransactionsMenue();
		break;
	case eMainMenue:system("cls");
		showMainMenue();
		break;



	}
}
void showTransactionsMenueScreen() {
	system("cls");
	cout << "=========================================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "=========================================================\n";
	cout << "\t[1] Deposite.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "=========================================================\n";
	performTransactionMenueOption((enTransactionMenueOptions)readTransactionsMenueOption());
}
void showMainMenue() {
	system("cls");
	cout << "=========================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "=========================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	cout << "=========================================================\n";
	performMainMenueOption((enMainMenueOptions)readMainMenueOption());


}
int main()
{
	showMainMenue();
}

