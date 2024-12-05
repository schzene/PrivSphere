






add_subdirectory(nexustools)
add_subdirectory(cheetahtools)



add_library(PrivaSphere-he 
cheetah-op.cpp
)




target_include_directories(PrivaSphere-he
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR}
 ${SEAL_INCLUDE_DIRS}
)

target_link_libraries(PrivaSphere-he
    PUBLIC
    cheetah-tools
)







