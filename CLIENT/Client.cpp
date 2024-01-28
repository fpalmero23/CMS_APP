/**
 * @file Client.cpp
 * @author Fernando Palmero
 * @brief Source file containing the client class. This class contains data relevant to the customer's personal information.
 * @version 0.1
 * @date 2024-01-24
 */

#include "Client.h"

C_Client::C_Client()
{

}

C_Client::C_Client(std::string Name, std::string AccountNumber):ClientName(Name),AccountNumber(AccountNumber)
{

}

C_Client::~C_Client()
{
    
}

const std::string& C_Client::GetClientName() const
{
    return ClientName;
}

const std::string& C_Client::GetAccountNumber() const
{
    return AccountNumber;
}