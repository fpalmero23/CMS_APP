#include "Bank.h"
#include <gtest/gtest.h>
#include <memory>

class ParametrizedTestBank : public ::testing::TestWithParam<std::tuple<std::string,std::string,double>> 
{
};

INSTANTIATE_TEST_SUITE_P(Parameters, ParametrizedTestBank, ::testing::Values(
    std::make_tuple("Blanca Palmero","123456789",200.5), 
    std::make_tuple("Cristina Perez","165478237",300.5), 
    std::make_tuple("Javier Martin","187436745",10.5), 
    std::make_tuple("Alejandro Alvarez","984563787",40.0), 
    std::make_tuple("Elena Garcia","987654321",500.4)
));

TEST_P(ParametrizedTestBank, TestBankUnorderMapsSize) 
{
    std::unique_ptr<C_Bank> BankInstance = std::make_unique<C_Bank>();
    std::tuple<std::string,std::string,double> param = GetParam();
    std::string Name = std::get<0>(param);
    std::string AccountNumber = std::get<1>(param);
    double Balance = std::get<2>(param);
    int Counter = 0;

    BankInstance->AddClient(Name,AccountNumber,Balance);
    auto result = BankInstance->GetAccount_umap();
    Counter++;
    EXPECT_EQ(result.size(), Counter);
}

TEST_P(ParametrizedTestBank, TestBankBalance) 
{
    std::unique_ptr<C_Bank> BankInstance = std::make_unique<C_Bank>();
    std::tuple<std::string,std::string,double> param = GetParam();
    std::string Name = std::get<0>(param);
    std::string AccountNumber = std::get<1>(param);
    double Balance = std::get<2>(param);
    
    BankInstance->AddClient(Name,AccountNumber,Balance);
    EXPECT_EQ(Balance, BankInstance->RequestBalanceByClientName(Name));
}


TEST_P(ParametrizedTestBank, TestBankDepositMoney)
{
    std::unique_ptr<C_Bank> BankInstance = std::make_unique<C_Bank>();
    std::tuple<std::string,std::string,double> param = GetParam();
    std::string Name = std::get<0>(param);
    std::string AccountNumber = std::get<1>(param);
    double Balance = std::get<2>(param);
    double Ammount = 50.0;

    BankInstance->AddClient(Name,AccountNumber,Balance);
    BankInstance->DepositMoney(Name,Ammount);
    EXPECT_EQ(BankInstance->RequestBalanceByClientName(Name),Balance + Ammount);
}

TEST_P(ParametrizedTestBank, TestBankCashOut)
{
    std::unique_ptr<C_Bank> BankInstance = std::make_unique<C_Bank>();
    std::tuple<std::string,std::string,double> param = GetParam();
    std::string Name = std::get<0>(param);
    std::string AccountNumber = std::get<1>(param);
    double Balance = std::get<2>(param);
    double Ammount = 50.0;

    BankInstance->AddClient(Name,AccountNumber,Balance);

    if(Ammount <= Balance)
    {
        BankInstance->CashOut(Name,Ammount);
        double NewBalance = BankInstance->RequestBalanceByClientName(Name);
        EXPECT_EQ(NewBalance,Balance - Ammount);
    }
    else
    {
        //EXPECT_THROW(BankInstance->CashOut(Name,Ammount), C_MyException);
        EXPECT_EQ(Balance,BankInstance->RequestBalanceByClientName(Name));
    }
}

TEST_P(ParametrizedTestBank, TestBankCheckNameSavedInSystem)
{
    std::unique_ptr<C_Bank> BankInstance = std::make_unique<C_Bank>();
    std::tuple<std::string,std::string,double> param = GetParam();
    std::string Name = std::get<0>(param);
    std::string AccountNumber = std::get<1>(param);
    double Balance = std::get<2>(param);

    BankInstance->AddClient(Name,AccountNumber,Balance);
    EXPECT_TRUE(BankInstance->CheckNameSavedInSystem(Name));
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    getchar();

    return 0;
}