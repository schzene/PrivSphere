# set(CMAKE_FIND_DEBUG_MODE 1)
include_directories(${CMAKE_CURRENT_LIST_DIR})

find_package(Eigen3 3.3 QUIET NO_MODULE PATHS "${PROJECT_SOURCE_DIR}/extern/eigen/build" NO_DEFAULT_PATH)
if (NOT Eigen3_FOUND)
    message(STATUS "Eigen 3.3 was not found: clone and install Eigen3 locally")
    if (NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/eigen/CMakeLists.txt")
        find_package(Git REQUIRED)
        message(STATUS "initialize Git submodule: extern/eigen")
        execute_process(COMMAND git submodule update --init --recursive extern/eigen
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory build
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/extern/eigen/")
    execute_process(COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${PROJECT_SOURCE_DIR}/build ..
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/extern/eigen/build")
    find_package(Eigen3 3.3 REQUIRED NO_MODULE PATHS "${PROJECT_SOURCE_DIR}/extern/eigen/build" NO_DEFAULT_PATH)
endif()

add_subdirectory(OT)
add_subdirectory(GC)
add_subdirectory(Millionaire)
add_subdirectory(BuildingBlocks)
add_subdirectory(LinearOT)
add_subdirectory(NonLinear)
add_subdirectory(Math)
add_subdirectory(FloatingPoint)

add_library(SCI-common INTERFACE)

find_package(Threads REQUIRED)

target_link_libraries(SCI-common
    INTERFACE
    SCI-BuildingBlocks
    SCI-FloatingPoint
    SCI-GC
    SCI-LinearOT
    SCI-Math
    SCI-Millionaire
    SCI-NonLinear
    SCI-OTPrimitive
    Threads::Threads
)