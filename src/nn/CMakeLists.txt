add_library(ps-nn
    bert.cpp
    resnet.cpp
)
 
 
target_link_libraries(ps-nn
    PUBLIC
    ps-protocols
)