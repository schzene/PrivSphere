


add_library(nexus-tools
nexus_ckks_evaluator.cpp
)
find_package(SEAL 4.1.2 EXACT QUIET PATHS "${PROJECT_SOURCE_DIR}/build/" NO_DEFAULT_PATH)
target_link_libraries(nexus-tools
    SEAL::seal
)








