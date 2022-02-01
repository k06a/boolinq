# Common variables.
CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (boolinq VERSION 3.0.5 LANGUAGES CXX)
INCLUDE (Dart)


SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG")


OPTION (BUILD_TESTS "Build unit tests" ON)
OPTION (BUILD_BENCHMARK "Build benchmark" ON)


# Static code analyse.
SET (CppCheck_REPORT ${PROJECT_BINARY_DIR}/cppcheck.report)
ADD_CUSTOM_COMMAND (
    OUTPUT  ${CppCheck_REPORT}
    COMMAND cppcheck ${PROJECT_SOURCE_DIR}/include/boolinq/boolinq.h --enable=all --force --inconclusive &>cppcheck.report
)
ADD_CUSTOM_TARGET  (cppcheck DEPENDS ${CppCheck_REPORT})
SET_DIRECTORY_PROPERTIES (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${CppCheck_REPORT})


# Testing.
IF (BUILD_TESTS OR BUILD_BENCHMARK)
    FIND_PACKAGE(GTest QUIET)
    IF (NOT GTest_FOUND)
        ADD_SUBDIRECTORY (externals/googletest)
    ENDIF ()
ENDIF()

IF (BUILD_TESTS)
    ADD_SUBDIRECTORY (test)
    IF (NOT GTest_FOUND)
        ADD_DEPENDENCIES ("${PROJECT_NAME}-test" gtest)
        ADD_DEPENDENCIES ("${PROJECT_NAME}-test14" gtest)
    ENDIF ()
ENDIF ()

IF (BUILD_BENCHMARK)
    FIND_PACKAGE(benchmark QUIET)
    IF (NOT benchmark_FOUND)
        ADD_SUBDIRECTORY (externals/benchmark)
        ADD_SUBDIRECTORY (bench)
        ADD_DEPENDENCIES ("${PROJECT_NAME}-bench" benchmark)
    ELSE ()
        ADD_SUBDIRECTORY (bench)
    ENDIF ()
ENDIF ()
