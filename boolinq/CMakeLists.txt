# Common variables.
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wundef -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Winit-self -Wvector-operation-performance -Wnoexcept -Weffc++ -Wstrict-null-sentinel")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wsign-promo")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op -Wcast-align")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith -Wtrampolines")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
SET (CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


# Unit tests.
SET (
    BoolinqTest_SOURCES
    ${PROJECT_SOURCE_DIR}/boolinq/AllTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/AnyTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/AvgTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/BitsRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/BytesRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ConcatRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ContainsTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/CountTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/DistinctRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/DotCallTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ElementAtTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ForeachTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/GroupByRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/IterRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/LinqTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/MaxTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/MinTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/OrderByRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ReverseRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/SelectRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/SkipRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/SkipWhileRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/SumTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/TakeRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/TakeWhileRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ToDequeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ToListTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ToSetTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/ToVectorTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/UnbitsRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/UnbytesRangeTest.cpp
    ${PROJECT_SOURCE_DIR}/boolinq/WhereRangeTest.cpp
)
ADD_EXECUTABLE (boolinqtest ${BoolinqTest_SOURCES})
TARGET_LINK_LIBRARIES (boolinqtest gtest gtest_main gcov pthread)
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


# Benchmarks.
SET (
    BoolinqBenchmark_SOURCES
    ${PROJECT_SOURCE_DIR}/boolinq/SpeedTest.cpp
)
ADD_EXECUTABLE (boolinqbenchmark ${BoolinqBenchmark_SOURCES})
TARGET_LINK_LIBRARIES (boolinqbenchmark gtest pthread benchmark)
