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
        src/util/csv.cpp
        src/DataRepository.cpp
        src/main.cpp
        src/util/Matrix.cpp
        src/ParameterEstimator.cpp
        src/ParameterEstimator.h
        src/PortfolioOptimiser.cpp
        src/PortfolioOptimiser.h
        src/util/VectorUtil.cpp
        src/util/VectorUtil.h
        src/Portfolio.cpp
        src/Portfolio.h)


add_executable(markowitzportfoliooptimiser ${SOURCE_FILES})
target_link_libraries(markowitzportfoliooptimiser)