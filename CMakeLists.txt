cmake_minimum_required(VERSION 3.15)
project(markowitzportfoliooptimiser)
set(CMAKE_CXX_STANDARD 14)

#set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -static-libasan -g3")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g3 -static-libasan")
# static-libasan is for address sanitiser
# -g3 is for verbosity of debug output

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g3")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g3")
set(SOURCE_FILES
        src/repository/csv.cpp
        src/repository/DataRepository.cpp
        src/backtest/main.cpp
        src/util/Matrix.cpp
        src/estimator/ParameterEstimator.cpp
        src/estimator/ParameterEstimator.h
        src/optimiser/PortfolioOptimiser.cpp
        src/optimiser/PortfolioOptimiser.h
        src/util/VectorUtil.cpp
        src/util/VectorUtil.h
        src/util/RunConfig.h src/util/Results.h)


add_executable(markowitzportfoliooptimiser ${SOURCE_FILES})
target_link_libraries(markowitzportfoliooptimiser)