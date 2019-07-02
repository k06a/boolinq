# Common variables.
#SET (CMAKE_BUILD_TYPE Release)
SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wfloat-equal -Wshadow")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Winit-self -Weffc++")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wsign-promo")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")


INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/include/boolinq)
INCLUDE_DIRECTORIES (${CMAKE_BINARY_DIR}/benchmark-src/include)
INCLUDE_DIRECTORIES (${CMAKE_BINARY_DIR}/googletest-src/googletest/include)


# Benchmarks.
SET (
    BoolinqBench_SOURCES
    ${PROJECT_SOURCE_DIR}/bench/SpeedTest.cpp
)
ADD_EXECUTABLE (
    "${PROJECT_NAME}-bench"
    ${BoolinqBench_SOURCES}
)
TARGET_LINK_LIBRARIES (
    "${PROJECT_NAME}-bench"
    benchmark
    gtest
)
