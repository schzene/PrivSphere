
add_library(cheetah-core-utils
    math.cc
    seal.cc
)
find_package(SEAL 4.1.2 EXACT QUIET PATHS "${PROJECT_SOURCE_DIR}/build/" NO_DEFAULT_PATH)

target_link_libraries(cheetah-core-utils
    PUBLIC
    SEAL::seal
    # OpenMP::OpenMP_CXX
    # Eigen3::Eigen
)