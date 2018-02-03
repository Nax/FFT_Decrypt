cmake_minimum_required(VERSION 3.10)
project(FFT_Decrypt)

include(CPack)

option(NO_GUI "Disable the Qt frontend" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

include_directories(include)
add_subdirectory(src)
