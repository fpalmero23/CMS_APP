/**
 * @file Bank.h
 * @author Fernando Palmero
 * @brief Header file containing the bank class. This class contains the data and functions necessary to interact with the client.
 * @version 0.1
 * @date 2024-01-24
 */

#pragma once

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "Client.h"
#include "Account.h"
#include "Exceptions.h"

class C_Bank 
{
    public:
        /**
         * @brief Constructor
         */
        C_Bank();
        /**
         * @brief Destructor
         */
        ~C_Bank();
        /**
         * @brief Function to get the only instance of the class (Singleton way)
         */
        static std::shared_ptr<C_Bank> getInstanceBank();
        /**
         * @brief Function to get map which contains de data client
         */
        std::unordered_map<std::string, std::tuple<C_Client,C_Account>> GetAccount_umap();
        /**
         * @brief Function to add client to the system
         * @param Name Client Name
         * @param AccountNumber Client Account Number
         * @param Balance Client Balance
         */
        void AddClient(std::string Name, std::string AccountNumber, double Balance);
        /**
         * @brief Show all the data of every client saved in the system
         */
        void ShowAllClientsData();
        /**
         * @brief Show all the data of one client of the system
         * @param Name Client Name to search
         */
        void ShowDataOneClientDataByName(std::string Name);
        /**
         * @brief Get the balance of one client
         * @param Name Client Name to search
         */
        double RequestBalanceByClientName(std::string Name);
        /**
         * @brief Function to deposit money in the system
         * @param Name Client Name
         * @param Ammount Ammount to deposit in the system
         */
        void DepositMoney(std::string Name, double Ammount);
        /**
         * @brief Function to cash out money of the system
         * @param Name Client Name
         * @param Ammount Ammount to cash out of the system
         */
        void CashOut(std::string Name, double Ammount);
        /**
         * @brief Function to check if a name is saved in the system
         * @param Name Client Name
         * @return True: Name exists in the system.
         */
        bool CheckNameSavedInSystem(std::string Name);
    private:
        std::unordered_map<std::string, std::tuple<C_Client,C_Account>> Account_umap;
        static std::shared_ptr<C_Bank> BankInstance;
};
