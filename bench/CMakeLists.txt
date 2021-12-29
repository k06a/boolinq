# Common variables.
#SET (CMAKE_BUILD_TYPE Release)
SET (CMAKE_CXX_STANDARD 11)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wmissing-include-dirs -Wfloat-equal -Wshadow")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Weffc++ -Woverloaded-virtual -Wsign-promo")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvla -Winvalid-pch -Winline -Wredundant-decls -Wcast-align")
SET (TARGET "${PROJECT_NAME}-bench" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wpointer-arith -Wold-style-cast")


INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/include/boolinq)
INCLUDE_DIRECTORIES (${CMAKE_BINARY_DIR}/benchmark-src/include)
INCLUDE_DIRECTORIES (${CMAKE_BINARY_DIR}/googletest-src/googletest/include)


# Benchmarks.
ADD_EXECUTABLE (
    "${PROJECT_NAME}-bench"
    ${PROJECT_SOURCE_DIR}/bench/SpeedTest.cpp
)
TARGET_LINK_LIBRARIES (
    "${PROJECT_NAME}-bench"
    benchmark
    gtest
)
