cmake_minimum_required(VERSION 3.15)
project(markowitzportfoliooptimiser)
set(CMAKE_CXX_STANDARD 14)
add_executable(
        markowitzportfoliooptimiser
        src/util/csv
        src/DataRepository
        src/main
        src/util/Matrix
)