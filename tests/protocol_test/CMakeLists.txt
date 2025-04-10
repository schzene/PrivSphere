include_directories(${PROJECT_SOURCE_DIR}/src)

macro (add_test name)
    add_executable(${name} "${name}.cpp")
    target_link_libraries(${name} PrivaSphere)
endmacro()