add_library(PrivaSphere-fp
    ring-op.cpp
    bool-op.cpp
)

target_include_directories(PrivaSphere-fp
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(PrivaSphere-fp
    PUBLIC
    PrivaSphere-comm
    PrivaSphere-ot
    PrivaSphere-baseprot
)





