add_subdirectory(costmodel)
add_subdirectory(cryptools)
add_subdirectory(neuralnet)
add_subdirectory(protocols)



add_library(PrivaSphere
    INTERFACE
)

target_include_directories(PrivaSphere
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:./>
)

target_link_libraries(PrivaSphere
    INTERFACE
    PrivaSphere-cryptools
    PrivaSphere-nn
    PrivaSphere-protocols
)