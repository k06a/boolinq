# Common variables.
SET (CMAKE_BUILD_TYPE "Release")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wundef -Wfloat-equal -Wshadow -Wunsafe-loop-optimizations")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Winit-self -Wvector-operation-performance -Wnoexcept -Weffc++ -Wstrict-null-sentinel")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wsign-promo")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op -Wcast-align")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith -Wtrampolines")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")


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
    pthread
    benchmark
)
