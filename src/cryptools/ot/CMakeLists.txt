add_library(PrivaSphere-ot INTERFACE)

target_include_directories(PrivaSphere-ot
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(PrivaSphere-ot
    INTERFACE
    PrivaSphere-comm
)