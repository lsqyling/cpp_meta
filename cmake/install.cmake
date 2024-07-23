
install(TARGETS meta
        EXPORT meta_targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY "${meta_SOURCE_DIR}/include/meta"
        DESTINATION include
)

install(EXPORT meta_targets
        FILE meta_targets.cmake
        NAMESPACE meta::
        DESTINATION lib/cmake/meta
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${meta_SOURCE_DIR}/cmake/templates/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/meta-config.cmake"
        INSTALL_DESTINATION lib/cmake/meta
)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/meta-config-version.cmake"
        COMPATIBILITY SameMinorVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/meta-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/meta-config-version.cmake"
        DESTINATION lib/cmake/meta
)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
            "${meta_SOURCE_DIR}/cmake/templates/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
