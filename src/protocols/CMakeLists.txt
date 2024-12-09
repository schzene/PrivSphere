include_directories(${PROJECT_SOURCE_DIR}/src)


add_library(PrivaSphere-protocols
    protocols.cpp
)

target_include_directories(PrivaSphere-protocols
    INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
)



target_link_libraries(PrivaSphere-protocols
    PUBLIC
    PrivaSphere-cryptools
)