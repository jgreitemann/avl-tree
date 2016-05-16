cmake_minimum_required (VERSION 2.6)
project (avl-tree CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(INSTALL_CMAKE_DIR CMake)
configure_file (avl-tree-config.cmake.in avl-tree-config.cmake)
install (FILES ${PROJECT_BINARY_DIR}/avl-tree-config.cmake
         DESTINATION ${INSTALL_CMAKE_DIR})
install (FILES avl_tree.hpp avl_traits.hpp DESTINATION include)

# The following Google Test setup has been derived from
# http://stackoverflow.com/questions/9689183/cmake-googletest

# Enable ExternalProject CMake module
include(ExternalProject)

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set default ExternalProject root directory
set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ThirdParty)

# Add gtest
ExternalProject_Add(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.7.0
    TIMEOUT 10
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
    -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
include_directories(${source_dir}/include)

# Add test executable target
include(${PROJECT_SOURCE_DIR}/tests/tests.cmake)
add_executable(avl_test EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/avl_test.cpp
    ${AVL_TEST_LIST})

# Create dependency of MainTest on googletest
add_dependencies(avl_test googletest)

# Specify avl_test's link libraries
ExternalProject_Get_Property(googletest binary_dir)
set(Suffix ".a")
set(Pthread "-pthread")
target_link_libraries(
    avl_test
    debug ${binary_dir}/DebugLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    optimized ${binary_dir}/ReleaseLibs/${CMAKE_FIND_LIBRARY_PREFIXES}gtest${Suffix}
    ${Pthread})

# Add a custom 'test' target that runs the googletest tests
add_custom_target(test avl_test DEPENDS avl_test)
