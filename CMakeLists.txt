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

# Menambahkan file sumber secara dinamis menggunakan GLOB
file(GLOB SOURCES
    "src/*.c"
    "src/logic/*.c"
)

add_executable(app ${SOURCES})

# Custom command untuk memantau perubahan file sumber
add_custom_target(auto_build ALL
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}
    COMMENT "Membangun aplikasi setelah perubahan file."
)

# Logika tambahan: Verifikasi generator dan konfigurasi
message(STATUS "Generator: ${CMAKE_GENERATOR}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Project source dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "Executable output dir: ${CMAKE_BINARY_DIR}")

# Cek in-source build (pastikan build dilakukan di folder selain root)
if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed. Please lakukan 'cd build' lalu coba build ulang.")
endif()

# Cek jika menggunakan MinGW Makefiles di folder root
if(CMAKE_GENERATOR STREQUAL "MinGW Makefiles" AND "${PROJECT_BINARY_DIR}" STREQUAL "${PROJECT_SOURCE_DIR}")
    message(FATAL_ERROR "Tidak boleh menggunakan MinGW Makefiles di folder root. Harap lakukan build di direktori build.")
endif()
