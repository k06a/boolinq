# Common variables.
SET (CMAKE_BUILD_TYPE Release)
SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)
SET (TARGET boolinqbenchmark CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wfloat-equal -Wshadow")
SET (TARGET boolinqbenchmark CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Winit-self -Weffc++")
SET (TARGET boolinqbenchmark CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wsign-promo")
SET (TARGET boolinqbenchmark CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
SET (TARGET boolinqbenchmark CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
SET (TARGET boolinqbenchmark CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith")
SET (TARGET boolinqbenchmark CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")


INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/externals/benchmark/include)
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/include/boolinq)
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/externals/gtest/include)


# Benchmarks.
SET (
    BoolinqBenchmark_SOURCES
    ${PROJECT_SOURCE_DIR}/benchmark/SpeedTest.cpp
)
ADD_EXECUTABLE (
    boolinqbenchmark
    ${BoolinqBenchmark_SOURCES}
)
TARGET_LINK_LIBRARIES (
    boolinqbenchmark
    gtest
    benchmark
)
