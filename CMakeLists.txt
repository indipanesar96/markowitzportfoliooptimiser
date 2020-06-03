cmake_minimum_required(VERSION 3.15)
project(markowitzportfoliooptimiser)
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        src/util/csv.cpp
        src/DataRepository.cpp
        src/main.cpp
        src/util/Matrix.cpp
        test/MatrixTests.cpp src/ParameterEstimator.cpp src/ParameterEstimator.h src/PortfolioOptimiser.cpp src/PortfolioOptimiser.h src/util/VectorUtil.cpp src/util/VectorUtil.h src/Portfolio.cpp src/Portfolio.h)
add_subdirectory(lib/gtest-1.10)
include_directories(lib/gtest-1.10/googletest/include)
include_directories(lib/gtest-1.10/googlemock/include)

add_executable(markowitzportfoliooptimiser ${SOURCE_FILES})
target_link_libraries(markowitzportfoliooptimiser gtest gtest_main)