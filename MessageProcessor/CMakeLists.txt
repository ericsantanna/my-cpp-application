cmake_minimum_required(VERSION 3.11)
project(message_processor)

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_path(MESSAGE_FILTER_INCLUDE_DIR MessageFilter.h PATHS /usr/local/include /usr/include)
find_library(MESSAGE_FILTER_LIBRARY lib_message_filter PATHS /usr/local/lib /usr/lib)

include_directories(${MESSAGE_FILTER_INCLUDE_DIR})

add_executable(message_processor Main.cpp MessageProcessor.cpp)
target_link_libraries(message_processor PRIVATE ${MESSAGE_FILTER_LIBRARY} Threads::Threads)

add_executable(test_MessageProcessor test_MessageProcessor.cpp MessageProcessor.cpp)
target_link_libraries(test_MessageProcessor PRIVATE ${MESSAGE_FILTER_LIBRARY} Threads::Threads)

enable_testing()
add_test(NAME TestMessageProcessor COMMAND test_MessageProcessor)

install(TARGETS message_processor
        RUNTIME DESTINATION bin)