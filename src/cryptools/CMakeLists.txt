include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(he)
add_subdirectory(ss)
add_subdirectory(utils)

add_library(PrivaSphere-cryptools
    INTERFACE
)

target_link_libraries(PrivaSphere-cryptools
    INTERFACE
    PrivaSphere-he
    PrivaSphere-ss
    SCI-utils
)

target_include_directories(PrivaSphere-cryptools
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:./>
)