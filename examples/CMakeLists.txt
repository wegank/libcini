include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(hello hello.c)
target_link_libraries(hello cini)
