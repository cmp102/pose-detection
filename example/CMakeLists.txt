project(example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall --pedantic")

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")

add_subdirectory(../ openp)

file(GLOB_RECURSE ALLCPP ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(${PROJECT_NAME} ${ALLCPP})
target_include_directories(${PROJECT_NAME} PRIVATE include libs/cpp_confparser/include)
target_link_libraries(${PROJECT_NAME} openPose ${CMAKE_SOURCE_DIR}/libs/cpp_confparser/confparser.a)
