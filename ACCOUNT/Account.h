/**
 * @file Account.h
 * @author Fernando Palmero
 * @brief Header file containing the C_Account class. This class contains the data and functions necessary to interact with the account data client.
 * @version 0.1
 * @date 2024-01-24
 */

#pragma once

class C_Account 
{
    public:
        /**
         * @brief Empty constructor
         */
        C_Account();
        /**
         * @brief Default Constructor
         * @param Balance Client Balance
         */
        C_Account(double Balance);
        /**
         * @brief Destructor
         */
        ~C_Account();
        /**
         * @brief Get the balance client
         */
        const double& GetBalance() const;
        /**
         * @brief Function to deposit money in the account client
         * @param amount Ammount to deposit in the account client
         */
        void DepositMoney(double amount);
        /**
         * @brief Function to cash out money of the account client
         * @param amount Ammount to cash out of the account client
         */
        void CashOutMoney(double amount);
    private:
        double Balance;
};