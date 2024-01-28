set(FilesLibrary Bank.cpp)
add_library(BankLib ${FilesLibrary})
target_include_directories(BankLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(BankLib PUBLIC AccountLib ClientLib ExceptionsLib)
#UNIT TEST
add_executable(BankUnitTest BankUnitTest.cpp)
target_include_directories(BankUnitTest PUBLIC ${CMAKE_SOURCE_DIR}/LIBS/gtest/googletest/include)
target_link_libraries(BankUnitTest PUBLIC BankLib gtest_main)
set_target_properties(BankUnitTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})