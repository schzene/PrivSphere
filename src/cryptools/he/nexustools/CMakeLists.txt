find_package(SEAL REQUIRED PATHS "${CMAKE_BINARY_DIR}/SEAL" NO_DEFAULT_PATH)

add_subdirectory(bootstrapping/common)
add_subdirectory(bootstrapping)

add_library(nexus-tools
    bootstrapping.cpp
    gelu.cpp
    layer_norm.cpp
    ckks_evaluator.cpp
    softmax.cpp
    matrix_mul.cpp
    argmax.cpp
    
    encryptionparams.cpp
    evaluator.cpp
    ${COMMON_SOURCE_FILES}
    ${BOOTSTRAPPING_SOURCE_FILES}
    ${SEAL_INCLUDES_DIR}
)

target_include_directories(nexus-tools PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COMMON_HEADER_DIR}
    ${BOOTSTRAPPING_HEADER_DIR}
)

target_link_libraries(nexus-tools
    ntl gmp m pthread SEAL::seal
)