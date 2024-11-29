add_subdirectory(util)

add_library(cheetah-core
    logging.cc
    types.cc
)

target_link_libraries(cheetah-core
    PUBLIC
    cheetah-core-utils
)
