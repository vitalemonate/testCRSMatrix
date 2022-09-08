cmake_minimum_required(VERSION 3.0.0)
project(testCRSMatrix VERSION 0.1.0)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")

find_package(Ceres REQUIRED)
find_package(Eigen3)

include_directories(
    ${CERES_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
)
add_executable(testCRSMatrix main.cpp)
target_link_libraries(testCRSMatrix ${CERES_LIBRARIES})
