find_package(SEAL 4.1.2 EXACT QUIET PATHS "${CMAKE_BINARY_DIR}SEAL" NO_DEFAULT_PATH)
if (NOT SEAL_FOUND)
    message(STATUS "SEAL 4.1.2 was not found: clone and install SEAL locally")
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/SEAL/CMakeLists.txt")
        find_package(Git REQUIRED)
        message(STATUS "initialize Git submodule: extern/SEAL")
        execute_process(COMMAND git submodule update --init --recursive extern/SEAL
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
        execute_process(COMMAND git apply "${PROJECT_SOURCE_DIR}/cmake/seal.patch"
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/extern/SEAL")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory SEAL
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
    execute_process(COMMAND ${CMAKE_COMMAND} ${PROJECT_SOURCE_DIR}/extern/SEAL -DSEAL_THROW_ON_TRANSPARENT_CIPHERTEXT=OFF
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/SEAL")
    execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install -j 16 
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/SEAL/")
    find_package(SEAL 4.1.2 EXACT REQUIRED PATHS "${CMAKE_BINARY_DIR}/SEAL" NO_DEFAULT_PATH)
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

add_library(ps-protocols
    protocols.cpp
)

target_link_libraries(ps-protocols
    PUBLIC
)