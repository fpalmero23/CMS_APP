/**
 * @file Client.h
 * @author Fernando Palmero
 * @brief Header file containing the client class. This class contains data relevant to the customer's personal information.
 * @version 0.1
 * @date 2024-01-24
 */

#pragma once
#include <string>

class C_Client 
{
    public:
        /**
         * @brief Constructor
         */
        C_Client();
        /**
         * @brief Constructor
         * @param Name Client Name
         * @param AccountNumber Account Number Client
         */
        C_Client(std::string Name, std::string AccountNumber);
        /**
         * @brief Destructor
         */
        ~C_Client();
        /**
         * @brief Get the Client Name
         */
        const std::string& GetClientName() const;
        /**
         * @brief Get the Client Account Number
         */
        const std::string& GetAccountNumber() const;
    private:
        std::string ClientName;
        std::string AccountNumber;
};