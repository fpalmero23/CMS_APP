/**
 * @file Exceptions.cpp
 * @author Fernando Palmero
 * @brief Source file setting up the C_MyException class for custom exceptions
 * @version 0.1
 * @date 2024-01-24
 */

#include "Exceptions.h"

C_MyException::C_MyException(Type type, std::string details, int level):
m_type_num((int)type),
m_msg(details),
m_level(level)
{
    std::unordered_map<Type, std::string>::iterator it = m_typeMessageMap.find(type);
    if (it != m_typeMessageMap.end())
    {
        m_type = it->second;
    }
    else
    {
        m_type = "UnknownErrorCode";
    }
}

std::string C_MyException::what()
{
    std::string type_code = std::to_string(m_type_num);
    std::string msg = "Exception type: " + m_type + "\nDetails: " + m_msg + "\nNumExcep: " + type_code;
    return msg;
}

int C_MyException::get_level()
{
    return m_level;
}

C_MyException::~C_MyException() {};