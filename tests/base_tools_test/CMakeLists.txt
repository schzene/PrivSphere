include_directories(${PROJECT_SOURCE_DIR}/src)

macro (add_test name)
    add_executable(${name} "${name}.cpp")
    target_link_libraries(${name} PrivaSphere)
endmacro()

add_test(fixed_data)
add_test(fixed_comm)
add_test(fixed_nexus)