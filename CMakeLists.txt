cmake_minimum_required(VERSION 3.15)
project(SistemManajemenPasien VERSION 1.0 LANGUAGES C)

# Pastikan compiler C ditemukan
if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "Compiler C tidak ditemukan! Pastikan compiler sudah terinstal.")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Direktori header
include_directories(${PROJECT_SOURCE_DIR}/include)

# File sumber
set(SOURCES
    src/main.c
    src/logic/kamarLogic.c
    src/logic/pasienLogic.c
)

add_executable(app ${SOURCES})

# Logika tambahan: Verifikasi generator dan konfigurasi
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "Executable output dir: ${CMAKE_BINARY_DIR}")
