# Common variables.
CMAKE_MINIMUM_REQUIRED (VERSION 3.0)

IF (DEFINED PROJECT_NAME)
    set(BOOLINQ_SUBPROJECT ON)
ENDIF ()
PROJECT (boolinq VERSION 3.0.5 LANGUAGES CXX)

INCLUDE (CMakePackageConfigHelpers)
INCLUDE (GNUInstallDirs)
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


# Initialize CMake target.
ADD_LIBRARY (boolinq INTERFACE)
ADD_LIBRARY (boolinq::boolinq ALIAS boolinq)

TARGET_COMPILE_FEATURES (boolinq INTERFACE cxx_std_11)
TARGET_INCLUDE_DIRECTORIES (boolinq INTERFACE
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)


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


# Installation.
IF (NOT BOOLINQ_SUBPROJECT)
    WRITE_BASIC_PACKAGE_VERSION_FILE (
        ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    INSTALL (TARGETS boolinq EXPORT boolinqTargets)

    INSTALL (EXPORT boolinqTargets
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/boolinq
        NAMESPACE boolinq::
        FILE ${PROJECT_NAME}Config.cmake
    )

    INSTALL (FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/boolinq
    )

    INSTALL (DIRECTORY include/boolinq
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILES_MATCHING PATTERN "*.h"
    )
ENDIF ()
