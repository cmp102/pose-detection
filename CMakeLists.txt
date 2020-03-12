cmake_minimum_required(VERSION 2.8.12)

PROJECT(openPose)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall --pedantic")
add_definitions()



file(GLOB_RECURSE ALLCPP RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(myprogram ${ALLCPP} ${ALLHPP})
target_include_directories(myprogram PRIVATE src)
TARGET_LINK_LIBRARIES(myprogram ${OpenCV_LIBS})

