# Generic lab CMakeLists.txt
get_filename_component(_LAB_DIR "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
set(_TARGET "lab_${_LAB_DIR}")

file(GLOB _SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

if(NOT _SOURCES)
    message(WARNING "[${_TARGET}] No source files found -- skipping")
    return()
endif()

add_executable(${_TARGET} EXCLUDE_FROM_ALL ${_SOURCES})
target_include_directories(${_TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
enable_course_cpp23(${_TARGET})
