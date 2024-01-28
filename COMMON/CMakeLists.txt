set(FilesLibrary Exceptions.cpp)
add_library(ExceptionsLib ${FilesLibrary})
target_include_directories(ExceptionsLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})