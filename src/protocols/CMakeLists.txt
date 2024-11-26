
add_library(PrivaSphere-protocols
    protocols.cpp
)

target_include_directories(PrivaSphere-protocols
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR})



target_link_libraries(PrivaSphere-protocols
    PUBLIC
)