cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

project(PrivaSphere)
set(NAME "PrivaSphere")
project(PrivaSphere LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(INSTALL_DIR "${CMAKE_INSTALL_PREFIX}")
set(BUILD_DIR "${PROJECT_SOURCE_DIR}/build")
cmake_host_system_information(RESULT N
                              QUERY NUMBER_OF_LOGICAL_CORES)

message(STATUS "Build type (CMAKE_BUILD_TYPE): ${CMAKE_BUILD_TYPE}")

find_package(SEAL-bs QUIET PATHS "${CMAKE_BINARY_DIR}/SEAL-bs" NO_DEFAULT_PATH)
if (NOT SEAL-bs_FOUND)
    message(STATUS "SEAL-bs was not found: install SEAL locally")
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory SEAL-bs
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    execute_process(COMMAND ${CMAKE_COMMAND} ${PROJECT_SOURCE_DIR}/extern/SEAL-bs -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DSEAL_THROW_ON_TRANSPARENT_CIPHERTEXT=OFF -DSEAL_USE_CXX17_OPTION_STR=ON -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/SEAL-bs
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/SEAL-bs")
    execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install -j${N}
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/SEAL-bs")
    find_package(SEAL-bs REQUIRED PATHS "${CMAKE_BINARY_DIR}/SEAL-bs" NO_DEFAULT_PATH)
endif()

find_package(Eigen3 3.3 QUIET NO_MODULE PATHS "${CMAKE_BINARY_DIR}/eigen" NO_DEFAULT_PATH)
if (NOT Eigen3_FOUND)
    message(STATUS "Eigen 3.3 was not found: clone and install Eigen3 locally")
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/eigen/CMakeLists.txt")
        find_package(Git REQUIRED)
        message(STATUS "initialize Git submodule: extern/eigen")
        execute_process(COMMAND git submodule update --init --recursive extern/eigen
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory eigen
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    execute_process(COMMAND ${CMAKE_COMMAND} ${PROJECT_SOURCE_DIR}/extern/eigen
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/eigen")
    find_package(Eigen3 3.3 REQUIRED NO_MODULE PATHS "${CMAKE_BINARY_DIR}/eigen" NO_DEFAULT_PATH)
endif()

add_subdirectory(src)
option(PS-test "Build tests" ON)
if(PS-test)
    message(STATUS "Tests enabled")
    enable_testing()
    add_subdirectory(tests)
endif()