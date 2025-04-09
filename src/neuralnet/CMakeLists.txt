add_subdirectory(tools)

add_library(PrivaSphere-nn
    simplenet.cpp
)
 
target_include_directories(PrivaSphere-nn
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(PrivaSphere-nn
    PUBLIC
    PrivaSphere-nn_tool
)