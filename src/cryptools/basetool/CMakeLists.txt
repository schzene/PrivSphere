add_library(PrivaSphere-baseprot INTERFACE)

target_include_directories(PrivaSphere-baseprot
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})


find_package(Eigen3 3.3 QUIET NO_MODULE PATHS "${CMAKE_BINARY_DIR}/eigen" NO_DEFAULT_PATH)

target_link_libraries(PrivaSphere-baseprot
    INTERFACE
    PrivaSphere-ot
    PrivaSphere-comm
    Eigen3::Eigen
)