add_subdirectory(cheetahtools)
add_subdirectory(nexustools)

add_library(PrivaSphere-he 
    cheetah-op.cpp
)

target_include_directories(PrivaSphere-he PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PrivaSphere-he PUBLIC
    cheetah-tools
    nexus-tools
)