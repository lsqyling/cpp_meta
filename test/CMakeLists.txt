
file(GLOB_RECURSE test_list
        LIST_DIRECTORIES false
        CONFIGURE_DEPENDS *.cpp
)

foreach (_v ${test_list})
    get_filename_component(target_name ${_v} NAME_WE)
    add_executable(${target_name} ${_v})
    string(REGEX MATCH "test/meta/" catch ${_v})
    if (catch)
        target_link_libraries(${target_name} PRIVATE catch3 meta::meta)
    else ()
        message(${_v})
        target_link_libraries(${target_name} PRIVATE meta::meta)
    endif ()
endforeach ()
