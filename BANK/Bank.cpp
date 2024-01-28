/**
 * @file Bank.cpp
 * @author Fernando Palmero
 * @brief Header file containing the bank class. This class contains the data and functions necessary to interact with the client.
 * @version 0.1
 * @date 2024-01-24
 */

#include "Bank.h"

std::shared_ptr<C_Bank> C_Bank::BankInstance = nullptr;

C_Bank::C_Bank()
{

}

C_Bank::~C_Bank()
{

}

std::shared_ptr<C_Bank> C_Bank::getInstanceBank()
{
    if (BankInstance == nullptr) 
    {
        BankInstance = std::shared_ptr<C_Bank>(new C_Bank());
    }
    return BankInstance;
}

std::unordered_map<std::string, std::tuple<C_Client,C_Account>> C_Bank::GetAccount_umap()
{
    return Account_umap;
}

void C_Bank::AddClient(std::string Name, std::string AccountNumber, double Balance) 
{
    bool l_bNameAlreadyExists = false;
    bool l_bAccountAlreadyExists = false;

    try
    {
        /* Checking Client Name */
        if(!Name.empty())
        {
            /* Checking Client Account Number */
            if(!(AccountNumber.empty()) || AccountNumber.length() == 9)
            {
                /* Checking if the Name and Account Number already exists */
                for (const auto& par : Account_umap) 
                {
                    if (std::get<0>(par.second).GetClientName() == Name) 
                    {
                        l_bNameAlreadyExists = true;
                        std::string l_msg = "[C_Bank::AddClient] Name Client already exits: " + Name;
                        throw C_MyException(C_MyException::Type::ErrorClientNameAlreadyExists,l_msg,1);
                    }
                    if (std::get<0>(par.second).GetAccountNumber() == AccountNumber) 
                    {
                        l_bAccountAlreadyExists = true;
                        std::string l_msg = "[C_Bank::AddClient] Account Number already exits: " + AccountNumber;
                        throw C_MyException(C_MyException::Type::ErrorClientAccountAlreadyExists,l_msg,1);
                    }
                }
                /* Add the client */
                if (l_bNameAlreadyExists == false && l_bAccountAlreadyExists == false)
                {
                    Account_umap.emplace(Name,std::make_tuple(C_Client(Name, AccountNumber), C_Account(Balance)));
                }
            }
            else
            {
                std::string l_msg = "[C_Bank::AddClient] Invalid Account Number: " + AccountNumber;
                throw C_MyException(C_MyException::Type::ErrorInvalidClientAccountNumber,l_msg,1);
            }
        }
        else
        {
            std::string l_msg = "[C_Bank::AddClient] Invalid Name: " + Name;
            throw C_MyException(C_MyException::Type::ErrorInvalidClientName,l_msg,1);
        }
    }
    catch(C_MyException& e)
    {
        if (e.get_level() == DEBUG_LEVEL)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void C_Bank::ShowAllClientsData()
{
    std::vector<std::pair<std::string, std::tuple<C_Client, C_Account>>> vec(Account_umap.begin(), Account_umap.end());

    /*The system displays the client in alphabetical order.*/
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) 
    {
        return a.first < b.first;
    });

    for (const auto& par : vec) 
    {
        /* Print all the data */
        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Client Name: " << std::get<0>(par.second).GetClientName() << std::endl;
        std::cout << "Account Number: " << std::get<0>(par.second).GetAccountNumber() << std::endl;
        std::cout << "Balance: " << std::get<1>(par.second).GetBalance() << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
}

void C_Bank::ShowDataOneClientDataByName(std::string Name)
{
    try
    {
        auto it = Account_umap.find(Name);
        if (it != Account_umap.end())
        {
            /* Print all the data */
            std::cout << "-----------------------------------" << std::endl;
            std::cout << "Client Name: " << std::get<0>(it->second).GetClientName() << std::endl;
            std::cout << "Account Number: " << std::get<0>(it->second).GetAccountNumber() << std::endl;
            std::cout << "Balance: " << std::get<1>(it->second).GetBalance() << std::endl;
        }
        else
        {
            std::string l_msg = "[C_Bank::ShowDataOneClientDataByName] Name not found: " + Name;
            throw C_MyException(C_MyException::Type::ErrorClientNameNotFound,l_msg,1);
        }
        std::cout << "-----------------------------------" << std::endl;
    }
    catch(C_MyException& e)
    {
        if (e.get_level() == DEBUG_LEVEL)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    } 
}

double C_Bank::RequestBalanceByClientName(std::string Name)
{
    double l_dBalance = 0.0;
    
    try
    {
        auto it = Account_umap.find(Name);
        if (it != Account_umap.end())
        {
            l_dBalance = std::get<1>(it->second).GetBalance();
        }
        else
        {
            std::string l_msg = "[C_Bank::RequestBalanceByClientName] Name not found: " + Name;
            throw C_MyException(C_MyException::Type::ErrorClientNameNotFound,l_msg,1);
        }
    }
    catch(C_MyException& e)
    {
        if (e.get_level() == DEBUG_LEVEL)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
    return l_dBalance;
}

void C_Bank::DepositMoney(std::string Name, double Ammount)
{
    try
    {
        auto it = Account_umap.find(Name);
        if (it != Account_umap.end())
        {
            std::get<1>(it->second).DepositMoney(Ammount);
        }
        else
        {
            std::string l_msg = "[C_Bank::DepositMoney] Name not found: " + Name;
            throw C_MyException(C_MyException::Type::ErrorClientNameNotFound,l_msg,1);
        }
    }
    catch(C_MyException& e)
    {
        if (e.get_level() == DEBUG_LEVEL)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
}

void C_Bank::CashOut(std::string Name, double Ammount)
{
    try
    {
        auto it = Account_umap.find(Name);
        if (it != Account_umap.end())
        {
            if (Ammount <= std::get<1>(it->second).GetBalance())
            {
                std::get<1>(it->second).CashOutMoney(Ammount);
            }
            else
            {
                std::string l_msg = "[C_Bank::CashOut] Amount less than the balance, Ammount: " + std::to_string(Ammount);
                throw C_MyException(C_MyException::Type::ErrorInvalidAmmountToCashOut,l_msg,1);
            }
        }
        else
        {
            std::string l_msg = "[C_Bank::CashOut] Name not found: " + Name;
            throw C_MyException(C_MyException::Type::ErrorClientNameNotFound,l_msg,1);
        }
    }
    catch(C_MyException& e)
    {
        if (e.get_level() == DEBUG_LEVEL)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

bool C_Bank::CheckNameSavedInSystem(std::string Name)
{
    bool l_bNameInTheSystem = false;

    try
    {
        auto it = Account_umap.find(Name);
        if (it != Account_umap.end())
        {
            l_bNameInTheSystem = true;
        }
        else
        {
            std::string l_msg = "[C_Bank::CheckNameSavedInSystem] Name not found: " + Name;
            throw C_MyException(C_MyException::Type::ErrorClientNameNotFound,l_msg,1);
        }
    }
    catch(C_MyException& e)
    {
        if (e.get_level() == DEBUG_LEVEL)
        {
            std::cout << e.what() << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
    return l_bNameInTheSystem;
}
