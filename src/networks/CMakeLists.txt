add_library(ps-network
    bert.cpp
    resnet.cpp
)
 
 
target_link_libraries(ps-network
    PUBLIC
    ps-protocols
)