set(FilesLibrary Client.cpp)
add_library(ClientLib ${FilesLibrary})
target_include_directories(ClientLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})