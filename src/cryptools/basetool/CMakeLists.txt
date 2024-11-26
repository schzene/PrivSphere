add_library(PrivaSphere-baseprot INTERFACE)

target_include_directories(PrivaSphere-baseprot
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})


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

target_link_libraries(PrivaSphere-baseprot
    INTERFACE
    PrivaSphere-ot
    PrivaSphere-comm
    Eigen3::Eigen
)