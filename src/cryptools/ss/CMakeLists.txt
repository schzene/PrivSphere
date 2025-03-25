add_subdirectory(SCI)

add_library(PrivaSphere-ss
    ss.cpp
)

target_include_directories(PrivaSphere-ss PUBLIC 
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/SCI
)

target_link_libraries(PrivaSphere-ss PUBLIC
    SCI-common
)





