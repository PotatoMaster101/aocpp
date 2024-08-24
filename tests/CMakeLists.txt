configure_file(${CMAKE_CURRENT_SOURCE_DIR}/resources/test_input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_executable(tests test_area.cpp test_input.cpp test_pos.cpp)
target_link_libraries(tests aocpp)
add_test(NAME tests COMMAND tests)
