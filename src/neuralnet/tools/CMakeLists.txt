add_library(PrivaSphere-nn_tool
    data_process.cpp
)
 
target_include_directories(PrivaSphere-nn_tool
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(PrivaSphere-nn_tool
    PUBLIC
    PrivaSphere
)