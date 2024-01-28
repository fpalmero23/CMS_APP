/**
 * @file API_DB.h
 * @author Fernando Palmero
 * @brief Header file that has a Class C_API_DB containing functions to interact with the database.
 * @version 0.1
 * @date 2024-01-24
 */

#pragma once
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Exceptions.h"
#include "Bank.h"

using json = nlohmann::json;

class C_API_DB
{
	public:
		/**
         * @brief Constructor
         */
		C_API_DB();
		/**
         * @brief Destructor
         */
		~C_API_DB();
		/**
         * @brief Get Name Data Base in string format
         */
		const std::string GetNameDataBaseFile();
		/**
         * @brief Set Name Data Base in string format
         * @param Name Data base name
         */
		void SetNameDataBaseFile(std::string Name);
		/**
         * @brief Function to get the only instance of the class (Singleton way)
         */
		static std::shared_ptr<C_API_DB> getConfigurationObject();
		/**
         * @brief Set Name Data Base in std::filesystem::path format
         */
		std::filesystem::path RequestPathFileDataBase();
		/**
         * @brief Get Data Base file in bytes
         */
		std::uintmax_t RequestFileSize();
		/**
         * @brief Read the data base file in order to initialize the class members
         */
		void ReadDataBase();
		/**
         * @brief Write in the data base file the Client data
         */
		void WriteDataBase();
		/**
         * @brief Read a configuration file in order to set up some class members
         */
		void ReadConfigurationFile();
		/**
         * @brief Write a configuration file in order to save some class members
         */
		void WriteConfigurationFile();
	private:
		std::string NameDataBaseFile;
		std::string NameConfigurationfile;
		std::filesystem::path FolderPath;
		static std::shared_ptr<C_API_DB> API_DB_Instance;
};