add_library(PrivaSphere-nn
    simplenet.cpp
    logistic.cpp
)
 
target_include_directories(PrivaSphere-nn
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(PrivaSphere-nn
    PUBLIC
    PrivaSphere-protocols
)