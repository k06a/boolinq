# Common variables.
SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wfloat-equal -Wshadow")
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Winit-self -Weffc++ ")
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wsign-promo")
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith")
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
SET (TARGET boolinqtest CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
SET (CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/include/boolinq)
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/externals/gtest/include)


# Unit tests.
SET (
    BoolinqTest_SOURCES
    ${PROJECT_SOURCE_DIR}/test/AllTest.cpp
    ${PROJECT_SOURCE_DIR}/test/AnyTest.cpp
    ${PROJECT_SOURCE_DIR}/test/AvgTest.cpp
    ${PROJECT_SOURCE_DIR}/test/BitsRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/BytesRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ConcatRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ContainsTest.cpp
    ${PROJECT_SOURCE_DIR}/test/CountTest.cpp
    ${PROJECT_SOURCE_DIR}/test/DistinctRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/DotCallTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ElementAtTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ForeachTest.cpp
    ${PROJECT_SOURCE_DIR}/test/GroupByRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/IterRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/LinqTest.cpp
    ${PROJECT_SOURCE_DIR}/test/MaxTest.cpp
    ${PROJECT_SOURCE_DIR}/test/MinTest.cpp
    ${PROJECT_SOURCE_DIR}/test/OrderByRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ReverseRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/SelectRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/SkipRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/SkipWhileRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/SumTest.cpp
    ${PROJECT_SOURCE_DIR}/test/TakeRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/TakeWhileRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ToDequeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ToListTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ToSetTest.cpp
    ${PROJECT_SOURCE_DIR}/test/ToVectorTest.cpp
    ${PROJECT_SOURCE_DIR}/test/UnbitsRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/UnbytesRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/test/WhereRangeTest.cpp
)
ADD_EXECUTABLE (
    boolinqtest
    ${BoolinqTest_SOURCES}
)
TARGET_LINK_LIBRARIES (
    boolinqtest
    gtest_main
    #gcov
    pthread
)
ENABLE_TESTING ()
ADD_TEST (BoolinqTest boolinqtest)


# Test coverage report.
SET (Coverage_REPORT ${PROJECT_BINARY_DIR}/coverage.info)
SET (Coverage_DIR    ${PROJECT_BINARY_DIR}/coverage)
ADD_CUSTOM_COMMAND (
    OUTPUT  ${Coverage_REPORT}
    COMMAND lcov -q -c -f -b . -d ${PROJECT_BINARY_DIR}/boolinq -o ${Coverage_REPORT}
    COMMAND lcov -e ${Coverage_REPORT} '${PROJECT_SOURCE_DIR}/boolinq/*' -o ${Coverage_REPORT}
    COMMAND genhtml ${Coverage_REPORT} --legend --demangle-cpp -f -q -o ${Coverage_DIR}
    DEPENDS boolinqtest
)
ADD_CUSTOM_TARGET (coverage DEPENDS ${Coverage_REPORT})
# FIXME: Doesn't work correctly (require explicit call cmake when files appear).
FILE (GLOB_RECURSE Coverage_GCNO ${PROJECT_BINARY_DIR}/*.gcno)
FILE (GLOB_RECURSE Coverage_GCDA ${PROJECT_BINARY_DIR}/*.gcda)
LIST (APPEND Coverage_DATA "${Coverage_REPORT}")
LIST (APPEND Coverage_DATA "${Coverage_DIR}")
LIST (APPEND Coverage_DATA "${Coverage_GCNO}")
LIST (APPEND Coverage_DATA "${Coverage_GCDA}")
SET_DIRECTORY_PROPERTIES (PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${Coverage_DATA}")
