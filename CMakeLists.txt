cmake_minimum_required(VERSION 3.11)
project(my_cpp_application NONE)

enable_testing()
include(CTest)

add_subdirectory(MessageFilter)
add_subdirectory(MessageSender)
add_subdirectory(MessageProcessor)
