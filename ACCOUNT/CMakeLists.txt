set(FilesLibrary Account.cpp)
add_library(AccountLib ${FilesLibrary})
target_include_directories(AccountLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})