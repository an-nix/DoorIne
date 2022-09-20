cmake_minimum_required(VERSION 3.0.0)
project(DoorIn VERSION 0.1.0)


include(CTest)
enable_testing()



set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
set(CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(CURL_LIBRARY "-lcurl") 

find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})

add_subdirectory(${PROJECT_SOURCE_DIR}/src/lib/test)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/lib/live555)

add_executable(DoorIn src/main.cpp src/network/client.cpp src/network/clientComHandler.cpp src/network/server.cpp)
target_link_libraries(DoorIn Threads::Threads ${OpenCV_LIBS} ${CURL_LIBRARY} Test live555)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# ADD_SUBDIRECTORY( live ) 