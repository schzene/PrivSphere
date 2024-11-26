add_subdirectory(costmodel)
add_subdirectory(cryptools)
add_subdirectory(neuralnet)
add_subdirectory(protocols)



add_library(PrivaSphere-src
    INTERFACE
)

target_include_directories(PrivaSphere-src
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:./>
)