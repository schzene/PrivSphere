add_library(SCI-FloatingPoint fixed-point.cpp bool-data.cpp)
target_link_libraries(SCI-FloatingPoint
    PUBLIC SCI-BuildingBlocks SCI-Math
)
