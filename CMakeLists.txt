#COMPILE CONFIGURATION
cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER gcc)
add_compile_options(/W3)
#CONFIGURATION PROJECT
set(This MainApp)
project(${This})
#GTEST WINDOWS CONFIGURATION
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()
#INCLUDE FOLDERS
add_subdirectory(ACCOUNT)
add_subdirectory(API_DB)
add_subdirectory(BANK)
add_subdirectory(CLIENT)
add_subdirectory(COMMON)
add_subdirectory(LIBS/googletest)
add_subdirectory(LIBS/json)
#THE EXECUTABLE IS ADDED
add_executable(${This} main.cpp)
#LINKING
target_link_libraries(${This} PUBLIC AccountLib API_DB_Lib BankLib ClientLib ExceptionsLib)
#Data Base files
set(API_DB_FolderPath "${CMAKE_CURRENT_SOURCE_DIR}/API_DB")
target_compile_definitions(API_DB_Lib PUBLIC API_DB_FolderPath="${API_DB_FolderPath}")
