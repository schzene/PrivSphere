
include_directories(${PROJECT_SOURCE_DIR}/src)





# cost_tets
macro(add_fix_func_test _name)
    add_executable(fix_${_name} "fixed_${_name}_test.cpp")
    target_link_libraries(fix_${_name} PrivaSphere-comm PrivaSphere-ot PrivaSphere-fp)
endmacro()


add_fix_func_test(comm)

