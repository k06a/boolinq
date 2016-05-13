# Common variables.
CMAKE_MINIMUM_REQUIRED  (VERSION 2.8)
PROJECT                 (boolinq)
SET (boolinq_VERSION_MAJOR 2)
SET (boolinq_VERSION_MINOR 0)


SET (CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -ggdb3 -DDEBUG -std=c++11")
SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -std=c++11")


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


# Testing.
ADD_SUBDIRECTORY (externals/gtest)
ADD_SUBDIRECTORY (externals/benchmark)
ADD_SUBDIRECTORY (test)
ADD_SUBDIRECTORY (benchmark)
ADD_DEPENDENCIES (boolinqbenchmark gtest)
ADD_DEPENDENCIES (boolinqbenchmark gtest_main)
ADD_DEPENDENCIES (boolinqbenchmark benchmark)
