include_directories(${CMAKE_CURRENT_LIST_DIR})
find_package(SEAL 4.1.2 EXACT QUIET PATHS "${CMAKE_BINARY_DIR}/SEAL/" NO_DEFAULT_PATH)
find_package(Eigen3 3.3 QUIET NO_MODULE PATHS "${CMAKE_BINARY_DIR}/eigen" NO_DEFAULT_PATH)

add_subdirectory(core)

add_library(cheetah-tools
    cheetah-api.cpp
    hom_bn_ss.cc
    hom_conv2d_ss.cc
    hom_fc_ss.cc
    shape_inference.cc
    tensor_encoder.cc
    tensor_shape.cc
)

target_include_directories(cheetah-tools
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(cheetah-tools
    cheetah-core
    SEAL::seal
    Eigen3::Eigen
    PrivaSphere-comm
)

