cmake_minimum_required(VERSION 3.22)
project(lib_message_filter)

set(CMAKE_CXX_STANDARD 11)

add_library(message_filter STATIC MessageFilter.cpp)

add_executable(test_message_filter test_MessageFilter.cpp)
target_link_libraries(test_message_filter message_filter)

enable_testing()
add_test(NAME TestMessageFilter COMMAND test_message_filter)

install(TARGETS message_filter
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

install(FILES MessageFilter.h DESTINATION include)
