cmake_minimum_required(VERSION 3.24)
project(embeddedville_secure_boot_capstone C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include(FetchContent)
set(ENABLE_PROGRAMS OFF CACHE BOOL "" FORCE)
set(ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(MBEDTLS_FATAL_WARNINGS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  mbedtls
  GIT_REPOSITORY https://github.com/Mbed-TLS/mbedtls.git
  GIT_TAG 0a8fda272a5a0abef3b47c91bed37185d5a726b1
  GIT_SHALLOW FALSE
  GIT_SUBMODULES_RECURSE TRUE
)
FetchContent_MakeAvailable(mbedtls)

add_library(secure_boot_student src/secure_boot_student.c)
target_include_directories(secure_boot_student PUBLIC include)
target_link_libraries(secure_boot_student PUBLIC TF-PSA-Crypto::tfpsacrypto)
target_compile_options(secure_boot_student PRIVATE -Wall -Wextra -Wpedantic)

enable_testing()
add_executable(public_checks tests/public_checks.c)
target_link_libraries(public_checks PRIVATE secure_boot_student)
add_test(NAME public_checks COMMAND public_checks)

if(DEFINED SECURE_BOOT_PROTECTED_TEST AND EXISTS "${SECURE_BOOT_PROTECTED_TEST}")
  add_executable(protected_checks "${SECURE_BOOT_PROTECTED_TEST}")
  target_link_libraries(protected_checks PRIVATE secure_boot_student)
  if(DEFINED SECURE_BOOT_STAGE)
    target_compile_definitions(protected_checks PRIVATE SECURE_BOOT_STAGE=${SECURE_BOOT_STAGE})
  endif()
  add_test(NAME protected_checks COMMAND protected_checks)
endif()

