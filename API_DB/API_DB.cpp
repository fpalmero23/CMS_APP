/**
 * @file API_DB.cpp
 * @author Fernando Palmero
 * @brief Source file that has a Class containing functions to interact with the database.
 * @version 0.1
 * @date 2024-01-24
 */

#include "API_DB.h"

std::shared_ptr<C_API_DB> C_API_DB::API_DB_Instance = nullptr;

/*Constructor */

C_API_DB::C_API_DB():NameDataBaseFile("DataBaseClients.json"),NameConfigurationfile("Configuration_API_DB.json"),FolderPath(API_DB_FolderPath)
{
    ReadConfigurationFile();
}

C_API_DB::~C_API_DB()
{

}

/* Encapsulaton Functions */
const std::string C_API_DB::GetNameDataBaseFile()
{
    return NameDataBaseFile;
}

void C_API_DB::SetNameDataBaseFile(std::string Name)
{
    try
    {
        /* 1. Checking Name */
        if (!Name.empty())
        {
            /* 2. Checking extension */
            if (Name.find(".json") <= Name.length())
            {
                std::filesystem::path l_old_path = RequestPathFileDataBase();
                std::filesystem::path l_new_path = std::filesystem::current_path() / Name;
                try
                {
                    std::filesystem::rename(l_old_path,l_new_path);
                    NameDataBaseFile = Name;
                }
                catch(const std::filesystem::filesystem_error& e)
                {
                    std::cout << e.what() << std::endl;
                }
            }
            else
            {
                std::string l_msg = "[C_API_DB::SetNameDataBaseFile] Invalid Name: " + Name;
                throw C_MyException(C_MyException::Type::ErrorInvalidDataBaseName,l_msg,1);
            }
        }
        else
        {
            std::string l_msg = "[C_API_DB::SetNameDataBaseFile] Invalid Name: " + Name;
            throw C_MyException(C_MyException::Type::ErrorInvalidDataBaseName,l_msg,1);
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

std::shared_ptr<C_API_DB> C_API_DB::getConfigurationObject()
{
    if (API_DB_Instance == nullptr) //IF NIVEL MAS ATRAS, MIRAR STATIC DENTRO FUNCION
    {
        API_DB_Instance = std::shared_ptr<C_API_DB>(new C_API_DB());
    }
    return API_DB_Instance;
}

/* General Functions */
std::filesystem::path C_API_DB::RequestPathFileDataBase()
{
    std::filesystem::path l_DirectoryPath = FolderPath;
    std::string l_path = l_DirectoryPath.generic_string() + "/" + GetNameDataBaseFile();
    return l_path;
}

std::uintmax_t C_API_DB::RequestFileSize()
{
    std::filesystem::path l_path = RequestPathFileDataBase();
    std::uintmax_t l_size = 0;

    try
    {
        l_size = std::filesystem::file_size(l_path);
    }
    catch(const std::filesystem::filesystem_error& e)
    {
        std::cout << e.what() << std::endl;
        l_size = 0;
    }
    
    return l_size;
}

void C_API_DB::ReadDataBase()
{
    std::filesystem::path l_path = RequestPathFileDataBase();
    std::ifstream l_file(l_path);
    std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();
    
    try
    {
        /* Open Data Base */
        if (!l_file.is_open()) 
        {
            std::string l_msg = "[C_API_DB::ReadDataBase] Cannot open the Data Base file in path: " + l_path.generic_string();
            throw C_MyException(C_MyException::Type::ErrorOpenDataBaseFile,l_msg,1);
        }
        /* Get JSON file content */
        json JSONData;
        l_file >> JSONData;
        /* Getting Clients */
        if (JSONData.contains("Clients") && JSONData["Clients"].is_array()) 
        {
            const auto& clientesJSON = JSONData["Clients"];
            for (const auto& clienteJSON : clientesJSON) 
            {
                /* Getting Name, Account Number and Account Balance */
                if (clienteJSON.contains("Name") && clienteJSON.contains("AccountNumber") && clienteJSON.contains("Balance")) 
                {
                    std::string ClientName = clienteJSON["Name"];
                    std::string AccountNumber = clienteJSON["AccountNumber"];
                    double Balance = clienteJSON["Balance"];
                    /* Add data client */
                    BankInstance->AddClient(ClientName,AccountNumber,Balance);
                }
            }
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

void C_API_DB::WriteDataBase()
{
    std::shared_ptr<C_Bank> BankInstance = C_Bank::getInstanceBank();
    std::filesystem::path l_path = RequestPathFileDataBase();
    std::ofstream l_file(l_path);
    json jsonData;
    std::unordered_map<std::string, std::tuple<C_Client,C_Account>> l_mapBankData = BankInstance->GetAccount_umap();

    try
    {
        if (!l_file.is_open()) 
        {
            std::string l_msg = "[C_API_DB::WriteDataBase] Cannot open the Data Base file in path: " + RequestPathFileDataBase().generic_string();
            throw C_MyException(C_MyException::Type::ErrorOpenDataBaseFile,l_msg,1);
        }
        
        for (const auto& client : l_mapBankData) 
        {
            json jsonClient = 
            {
                {"Name", std::get<0>(client.second).GetClientName()},
                {"AccountNumber", std::get<0>(client.second).GetAccountNumber()},
                {"Balance", std::get<1>(client.second).GetBalance() }
            };
            jsonData["Clients"].push_back(jsonClient);
        }

        /* Write tha data in JSON file */
        l_file.seekp(0);
        l_file << std::setw(4) << jsonData << std::endl;
        /* Close the file */
        l_file.close();
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

void C_API_DB::ReadConfigurationFile()
{
    try
    {
        /* Initialisation Values */
        std::filesystem::path l_FolderPath = FolderPath; //CMake Variable
        std::filesystem::path l_path = l_FolderPath / NameConfigurationfile;
        std::ifstream l_file(l_path);
        /* Open Data Base */
        if (!l_file.is_open()) 
        {
            std::string l_msg = "[C_API_DB::ReadConfigurationFile] Cannot open the Data Base file in path: " + l_path.generic_string();
            throw C_MyException(C_MyException::Type::ErrorOpenDataBaseFile,l_msg,1);
        }
        /* Get JSON file content */
        json JSONData;
        l_file >> JSONData;
        /* Getting Clients */
        if (JSONData.contains("Configuration") && JSONData["Configuration"].is_object()) 
        {
            const auto& ConfigurationJSON = JSONData["Configuration"];
            if (ConfigurationJSON.contains("NameDataBaseFile")) 
            {
                NameDataBaseFile = ConfigurationJSON["NameDataBaseFile"];
            }
        }
        l_file.close();
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

void C_API_DB::WriteConfigurationFile()
{
    try
    {
        std::filesystem::path l_FolderPath = FolderPath;
        std::filesystem::path l_path = l_FolderPath / NameConfigurationfile;
        std::fstream l_file(l_path, std::ios::in | std::ios::out);

        if (!l_file.is_open()) 
        {
            std::string l_msg = "[C_API_DB::WriteConfigurationFile] Cannot open the Data Base file in path: " + RequestPathFileDataBase().generic_string();
            throw C_MyException(C_MyException::Type::ErrorOpenDataBaseFile,l_msg,1);
        }

        /* Parse the JSON file */
        json JSONData;
        l_file >> JSONData;

        /*Checking the parse */
        if (JSONData.is_discarded()) 
        {
            std::string l_msg = "[C_API_DB::WriteConfigurationFile] Error parsing the following file: " + l_path.generic_string();
            throw C_MyException(C_MyException::Type::ErrorParseConfigurationFile,l_msg,1);
        }

        /* Modify the data */
        JSONData["Configuration"]["NameDataBaseFile"] = GetNameDataBaseFile();
        /* Write tha data in JSON file */
        l_file.seekp(0);
        l_file << std::setw(4) << JSONData << std::endl;
        /* Close the file */
        l_file.close();
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