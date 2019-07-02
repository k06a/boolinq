# Common variables.
CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()
PROJECT (boolinq VERSION 3.0.0 LANGUAGES CXX)


SET (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")


# Boolinq source code.
SET (
    Boolinq_INCLUDES
    ${PROJECT_SOURCE_DIR}/boolinq/boolinq.h
)


# Static code analyse.
SET (CppCheck_REPORT ${PROJECT_BINARY_DIR}/cppcheck.report)
ADD_CUSTOM_COMMAND (
    OUTPUT  ${CppCheck_REPORT}
    COMMAND cppcheck ${Boolinq_INCLUDES} --enable=all --force --inconclusive &>cppcheck.report
)
ADD_CUSTOM_TARGET  (cppcheck DEPENDS ${CppCheck_REPORT})
SET_DIRECTORY_PROPERTIES (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CppCheck_REPORT})


include(ExternalProject)
ExternalProject_Add(benchmark
        GIT_REPOSITORY    https://github.com/google/benchmark.git
        GIT_TAG           v1.5.0
        SOURCE_DIR        "${CMAKE_BINARY_DIR}/benchmark-src"
        BINARY_DIR        "${CMAKE_BINARY_DIR}/benchmark-build"
        CMAKE_ARGS        "-DBENCHMARK_ENABLE_GTEST_TESTS=OFF;-DCMAKE_BUILD_TYPE=Release"
        )

ExternalProject_Add(googletest
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           release-1.8.1
        SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest-src"
        BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest-build"
        CMAKE_ARGS        "-DCMAKE_BUILD_TYPE=Release"
        )

# Testing.
ADD_SUBDIRECTORY (test)
ADD_SUBDIRECTORY (bench)
ADD_DEPENDENCIES ("${PROJECT_NAME}-test" googletest)
ADD_DEPENDENCIES ("${PROJECT_NAME}-bench" benchmark)
