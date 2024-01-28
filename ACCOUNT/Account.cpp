/**
 * @file Account.cpp
 * @author Fernando Palmero
 * @brief Source file containing the account class. This class contains the data and functions necessary to interact with the account data client.
 * @version 0.1
 * @date 2024-01-24
 */

#include "Account.h"

C_Account::C_Account()
{

}

C_Account::C_Account(double balance):Balance(balance)
{

}

C_Account::~C_Account()
{
    
}

const double& C_Account::GetBalance() const
{
    return Balance;
}

void C_Account::DepositMoney(double amount)
{
    Balance = Balance + amount;
}

void C_Account::CashOutMoney(double Ammount)
{
    if (Ammount <= Balance)
    {
        Balance = Balance - Ammount;
    }
}
