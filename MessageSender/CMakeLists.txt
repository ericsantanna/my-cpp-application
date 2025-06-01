cmake_minimum_required(VERSION 3.11)
project(message_sender)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

enable_testing()
include(CTest)

add_library(message_sender_lib
        MessageSender.cpp
        MessageSender.h
)

add_executable(message_sender Main.cpp)
target_link_libraries(message_sender PUBLIC message_sender_lib PRIVATE Threads::Threads)

add_executable(test_MessageSender test_MessageSender.cpp)
target_link_libraries(test_MessageSender PUBLIC message_sender_lib PRIVATE Threads::Threads)

add_test(
        NAME MessageSenderTest
        COMMAND test_MessageSender
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/messages.txt ${CMAKE_BINARY_DIR}/MessageSender/messages.txt COPYONLY)

set_tests_properties(MessageSenderTest
        PROPERTIES
        PASS_REGULAR_EXPRESSION "All tests passed!"
        FAIL_REGULAR_EXPRESSION "test.*failed"
)

install(TARGETS message_sender
        RUNTIME DESTINATION bin
)