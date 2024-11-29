include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(fix_comm "fixed_comm_test.cpp")
target_link_libraries(fix_comm PrivaSphere)

add_executable(field_data "field_data_test.cpp")
target_link_libraries(field_data PrivaSphere)
