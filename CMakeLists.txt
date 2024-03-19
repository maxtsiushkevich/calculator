cmake_minimum_required(VERSION 3.24)

set(NAME calculator)
project(NAME)

file(GLOB_RECURSE source_files
    "src/*.cpp"
)
add_executable(${NAME} ${source_files} include/MyVector.hpp include/MyStack.hpp)

target_include_directories(${NAME} PRIVATE 
    "include/"
)

target_compile_features(${NAME} PRIVATE cxx_std_20)