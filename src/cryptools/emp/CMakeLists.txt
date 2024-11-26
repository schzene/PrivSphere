
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(cmake/source_of_randomness.cmake)

# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

find_package(OpenSSL REQUIRED)
FIND_PACKAGE(GMP REQUIRED)

add_library(PrivaSphere-comm INTERFACE)

target_compile_options(PrivaSphere-comm
    INTERFACE
    "-pthread;-maes;-msse4.1;-mavx;-mavx2;-faligned-new;-std=c++17;-O3;;-Wno-deprecated-declarations;")
if(USE_RANDOM_DEVICE)
    target_compile_definitions(PrivaSphere-comm INTERFACE EMP_USE_RANDOM_DEVICE=1)
else(USE_RANDOM_DEVICE)
    target_compile_options(PrivaSphere-comm  INTERFACE "-mrdseed")
endif(USE_RANDOM_DEVICE)



target_include_directories(PrivaSphere-comm
     INTERFACE ${OPENSSL_INCLUDE_DIR} ${GMP_INCLUDE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(PrivaSphere-comm
    INTERFACE ${OPENSSL_LIBRARIES} ${GMP_LIBRARIES}
)