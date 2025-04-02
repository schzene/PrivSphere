add_subdirectory(nexustools)

add_library(PrivaSphere-he 
    nexus-op.cpp
)

target_include_directories(PrivaSphere-he PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(PrivaSphere-he PUBLIC
    nexus-tools
)

add_executable(nexus_test "nexus_test.cpp")
target_link_libraries(nexus_test PUBLIC
    PrivaSphere-he
    nexus-tools
)