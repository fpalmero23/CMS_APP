/**
 * @file Main.cpp
 * @author Fernando Palmero
 * @brief Main file containing the functions that can be used by the administrator or the user
 * @version 0.1
 * @date 2024-01-24
 */

#include <iostream>
#include "API_DB.h"
#include "Bank.h"

void SetupApp();
void EnterUser();
void ShowMainMenuUser();
void ShowMainMenuAdmin();
void ExitConfiguration();
void AdminFunction_QueryDataAllClients();
void AdminFunction_QueryClientData();
void AdminFunction_RenameDataBaseFile();
void AdminFunction_QuerySizeDataBase();
void AdminFunction_AddClient();
void UserFunction_CashOut();
void UserFunction_DepositMoney();
void UserFunction_CheckBalance();

struct S_UserLoginData
{
	std::string ClientLoginName;
	bool UserLogin;
}ClientLoginData;

typedef void (*FuncPtr)();
std::map <std::string, FuncPtr> AdminFunctionsMap = 
{
    {"1. Query data of all customers", AdminFunction_QueryDataAllClients},
    {"2. Query client data", AdminFunction_QueryClientData},
    {"3. Rename Data Base file", AdminFunction_RenameDataBaseFile},
    {"4. Query Size of Data Base file", AdminFunction_QuerySizeDataBase},
    {"5. Add a Client", AdminFunction_AddClient}
};
std::map <std::string, FuncPtr> UserFunctionsMap = 
{
    {"1. Cash out", UserFunction_CashOut},
    {"2. Deposit Money", UserFunction_DepositMoney},
    {"3. Check Balance", UserFunction_CheckBalance},
};

int main()
{
	std::string l_sInputGeneral;
	int l_iAnswer = 0;
    int l_iExitOption = 0;

	/* Configuration of main variables */
	SetupApp();
	/* Enter User or Admin */
	EnterUser();
	/* User or Admin Menu */
    do
    {
		if (ClientLoginData.UserLogin == true)
		{
			ShowMainMenuUser();
			std::getline(std::cin, l_sInputGeneral);
			l_iAnswer = std::atoi(l_sInputGeneral.c_str());
			l_iExitOption = UserFunctionsMap.size() + (int) 1;
			if (l_iAnswer > 0 && l_iAnswer < l_iExitOption)
			{
				std::map <std::string, FuncPtr>::iterator it = UserFunctionsMap.begin();
				std::advance(it,l_iAnswer-1);
				it->second();
			}
		}
		else
		{
        	ShowMainMenuAdmin();
			std::getline(std::cin, l_sInputGeneral);
			l_iAnswer = std::atoi(l_sInputGeneral.c_str());
			l_iExitOption = AdminFunctionsMap.size() + (int) 1;
			if (l_iAnswer > 0 && l_iAnswer < l_iExitOption)
			{
				std::map <std::string, FuncPtr>::iterator it = AdminFunctionsMap.begin();
				std::advance(it,l_iAnswer-1);
				it->second();
			}
		}
    }while(l_iAnswer != l_iExitOption);

	ExitConfiguration();

	return 0;
}

void SetupApp()
{
	std::shared_ptr<C_API_DB> API_DB_Instance = C_API_DB::getConfigurationObject();

	/* Initialation Data Base */
	API_DB_Instance->ReadDataBase();
}

void EnterUser()
{
	std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();
	std::string l_sNameToFind;
	bool l_bNameInTheSystem = false;

	do
	{
		std::cout << "User: ";
		std::getline(std::cin, l_sNameToFind);
		if (l_sNameToFind == "Admin")
		{
			ClientLoginData.UserLogin = false;
			l_bNameInTheSystem = true;
		}
		else if (BankInstance->CheckNameSavedInSystem(l_sNameToFind) == true)
		{
			ClientLoginData.ClientLoginName = l_sNameToFind;
			ClientLoginData.UserLogin = true;
			l_bNameInTheSystem = true;
		}
	} while (l_sNameToFind.empty() || l_bNameInTheSystem == false);
}

void ShowMainMenuUser()
{
	std::cout << "1. Cash out" << std::endl;
	std::cout << "2. Deposit Money" << std::endl;
	std::cout << "3. Check Balance" << std::endl;
	std::cout << "4. Exit" << std::endl;
}

void ShowMainMenuAdmin()
{
	int l_iExitOption = AdminFunctionsMap.size() + (int) 1;

    for(std::map <std::string, FuncPtr> ::iterator it=AdminFunctionsMap.begin(); it!=AdminFunctionsMap.end(); ++it)  
    {  
        std::cout << (*it).first << std::endl;
    }
    /* Exit Option */
    std::cout << l_iExitOption<< ": Exit" << std::endl;
}

void ExitConfiguration()
{
	std::shared_ptr<C_API_DB> API_DB_Instance = C_API_DB::getConfigurationObject();

	API_DB_Instance->WriteDataBase();
	API_DB_Instance->WriteConfigurationFile();

	//IDEA: SE PUEDE VER ULTIMA FECHA DE MODIFICACION Y ASI NO SE REESCRIBE
}

void AdminFunction_QueryDataAllClients()
{
	std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();

	BankInstance->ShowAllClientsData();
}
void AdminFunction_QueryClientData()
{
	std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();
	std::string l_sNameToFind;

	do
	{
		std::cout << "Enter the full name in order to find the data: ";
		std::getline(std::cin, l_sNameToFind);
	} while (l_sNameToFind.empty());

	BankInstance->ShowDataOneClientDataByName(l_sNameToFind);
}
void AdminFunction_RenameDataBaseFile()
{
	std::shared_ptr<C_API_DB> API_DB_Instance = C_API_DB::getConfigurationObject();
	std::string l_sNewDataBaseName;

	do
	{
		std::cout << "Enter the new data base name: ";
		std::getline(std::cin, l_sNewDataBaseName);
	} while (l_sNewDataBaseName.empty());
	
	API_DB_Instance->SetNameDataBaseFile(l_sNewDataBaseName);
	std::cout << "Data Base file name: " << API_DB_Instance->GetNameDataBaseFile() << std::endl;
}

void AdminFunction_QuerySizeDataBase()
{
	std::shared_ptr<C_API_DB> API_DB_Instance = C_API_DB::getConfigurationObject();
	std::cout << API_DB_Instance->RequestFileSize() << " Bytes " <<std::endl;
}

void AdminFunction_AddClient()
{
	std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();
	std::string l_sClientName = "";
	std::string l_sAccountNumberClient = "";
	std::string l_sInitialBalance = "";
	double l_dInitialBalance = 0.0;

	do
	{
		std::cout << "Enter the new full name of the client: ";
		std::getline(std::cin, l_sClientName);
	} while (l_sClientName.empty());

	do
	{
		std::cout << "Enter the new number account (9 digits) of the client: ";
		std::getline(std::cin, l_sAccountNumberClient);
	} while (l_sAccountNumberClient.empty() || l_sAccountNumberClient.length() != 9);

	std::cout << "Enter the initial balance of the client: ";
	std::getline(std::cin, l_sInitialBalance);
	l_dInitialBalance = std::stod(l_sInitialBalance);

	BankInstance->AddClient(l_sClientName,l_sAccountNumberClient,l_dInitialBalance);
	std::cout << "\n";
}

void UserFunction_CashOut()
{
	std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();
	std::string l_sAmmount = "";
	double l_dAmmount = 0.0;
	double l_dBalance = BankInstance->RequestBalanceByClientName(ClientLoginData.ClientLoginName);

	std::cout << "Actual Balance: " << BankInstance->RequestBalanceByClientName(ClientLoginData.ClientLoginName) << std::endl;
	std::cout << "Enter the ammount to CashOut: ";
	std::getline(std::cin, l_sAmmount);
	l_dAmmount = std::stod(l_sAmmount);
	if (l_dAmmount <= l_dBalance)
	{
		BankInstance->CashOut(ClientLoginData.ClientLoginName, l_dAmmount);
		l_dBalance = BankInstance->RequestBalanceByClientName(ClientLoginData.ClientLoginName);
		std::cout << "New Balance: " << l_dBalance << std::endl;
	}
	else
	{
		std::cout << "You have to enter a Ammount upper to your Balance" << std::endl;
	}
}
void UserFunction_DepositMoney()
{
	std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();
	std::string l_sAmmount = "";
	double l_dAmmount = 0.0;
	double l_dBalance = BankInstance->RequestBalanceByClientName(ClientLoginData.ClientLoginName);

	std::cout << "Actual Balance: " << l_dBalance << std::endl;
	std::cout << "Enter the ammount to deposit: ";
	std::getline(std::cin, l_sAmmount);
	l_dAmmount = std::stod(l_sAmmount);
	BankInstance->DepositMoney(ClientLoginData.ClientLoginName, l_dAmmount);
	l_dBalance = BankInstance->RequestBalanceByClientName(ClientLoginData.ClientLoginName);
	std::cout << "New Balance: " << l_dBalance << std::endl;
}

void UserFunction_CheckBalance()
{
	std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();

	double l_dBalance = BankInstance->RequestBalanceByClientName(ClientLoginData.ClientLoginName);
	std::cout << "Balance: " << l_dBalance << std::endl;
}
