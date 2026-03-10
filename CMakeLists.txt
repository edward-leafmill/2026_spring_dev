cmake_minimum_required(VERSION 3.20)

project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GCC/libstdc++ on Windows requires libstdc++exp for std::print/std::println.
if(MINGW)
    link_libraries($<$<LINK_LANGUAGE:CXX>:stdc++exp>)
endif()

# Backward compatibility for lab templates that still call this helper.
function(enable_course_cpp23 target_name)
endfunction()

add_subdirectory(labs)
