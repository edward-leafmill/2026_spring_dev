file(GLOB LAB_SUBDIRS CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "q*")

add_custom_target(course_all_labs)

foreach(lab_dir IN LISTS LAB_SUBDIRS)
    set(lab_cmake "${CMAKE_CURRENT_SOURCE_DIR}/${lab_dir}/CMakeLists.txt")
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${lab_dir}" AND EXISTS "${lab_cmake}")
        add_subdirectory("${lab_dir}")
        if(TARGET "lab_${lab_dir}")
            add_dependencies(course_all_labs "lab_${lab_dir}")
        endif()
    endif()
endforeach()
