cmake_minimum_required(VERSION 3.7.2)
project(Variant 
        VERSION 0.0.1 
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option (USE_MPARK_VARIANT "use mpark variant" ON)
if (USE_MPARK_VARIANT)
include(cmake/CPM.cmake)
CPMFindPackage(
    NAME mpark_variant
    GITHUB_REPOSITORY mpark/variant
    VERSION 1.4.0
)
endif()        

set(TARGET_NAME ${PROJECT_NAME})
set(HEADERS 
    "include/Variant.h"
)
add_library(${TARGET_NAME} INTERFACE)
target_include_directories(${TARGET_NAME}
    INTERFACE 
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)
add_library(${PROJECT_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

if(USE_MPARK_VARIANT)
    target_compile_definitions(${TARGET_NAME} INTERFACE USE_MPARK_VARIANT="ON")
    target_link_libraries(${TARGET_NAME}
        INTERFACE mpark_variant
    )
endif()

option (BUILD_TESTS "build tests" ON)
if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(UnitTest)
endif()

include(GNUInstallDirs)

install(
    TARGETS ${TARGET_NAME} 
    EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

install(EXPORT ${PROJECT_NAME}-targets
  NAMESPACE  ${PROJECT_NAME}::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

if(USE_MPARK_VARIANT)
  set(MPARK_DEPENDENCY "find_dependency(mpark_variant REQUIRED)")
endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in 
               ${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake @ONLY)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" COMPATIBILITY SameMajorVersion)
install(FILES 
           "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake" 
           "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" 
        DESTINATION 
           "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")