/**
 * @file Exceptions.h
 * @author Fernando Palmero
 * @brief Header setting class C_MyException for custom exceptions
 * @version 0.1
 * @date 2024-01-24
 */

#pragma once
#include <exception>
#include <string>
#include <unordered_map>

#define DEBUG_LEVEL 1 /*0: User, 1: Debug */

class C_MyException : public std::exception
{
    public:
        /**
         * @brief Types of errors
         */
        enum class Type
        {
            ErrorOpenDataBaseFile = 0x01,
            ErrorInvalidDataBaseName = 0x02,
            ErrorParseConfigurationFile = 0x03,
            ErrorInvalidClientName = 0x04,
            ErrorInvalidClientAccountNumber= 0x05,
            ErrorClientNameAlreadyExists= 0x06,
            ErrorClientAccountAlreadyExists= 0x07,
            ErrorClientNameNotFound = 0x08,
            ErrorInvalidAmmountToCashOut= 0x09
        };
        /**
         * @brief Constructor
         */
        C_MyException(Type type, std::string details, int level);
        /**
         * @brief Destructor
         */
        ~C_MyException();
        /**
         * @brief Function to print the custom exceptions
         */
        std::string what();
        /**
         * @brief Level of the exception.
         * @return Level 0: User level. Level 1: Debug Level
         */
        int get_level();
    private:
        std::string m_msg;
        std::string m_type;
        int m_type_num;
        int m_level;
        std::unordered_map<C_MyException::Type, std::string> m_typeMessageMap =
        {
            { C_MyException::Type::ErrorOpenDataBaseFile, "ErrorOpenFile" },
            { C_MyException::Type::ErrorInvalidDataBaseName, "ErrorInvalidDataBaseName" },
            { C_MyException::Type::ErrorParseConfigurationFile, "ErrorParseConfigurationFile" },
            { C_MyException::Type::ErrorInvalidClientName, "ErrorInvalidClientName" },
            { C_MyException::Type::ErrorInvalidClientAccountNumber, "ErrorInvalidClientAccountNumber" },
            { C_MyException::Type::ErrorClientNameAlreadyExists, "ErrorClientNameAlreadyExists" },
            { C_MyException::Type::ErrorClientAccountAlreadyExists, "ErrorClientAccountAlreadyExists" },
            { C_MyException::Type::ErrorClientNameNotFound, "ErrorClientNameNotFound" },
            { C_MyException::Type::ErrorInvalidAmmountToCashOut, "ErrorInvalidAmmountToCashOut" },
        };
};
