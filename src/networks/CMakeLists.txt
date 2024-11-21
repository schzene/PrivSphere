add_library(ps-network
    bert.cpp
    resnet50.cpp
)
 
 
target_link_libraries(ps-network
    PUBLIC
    ps-protocols
)