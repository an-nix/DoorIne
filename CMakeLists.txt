cmake_minimum_required(VERSION 3.0.0)
project(DoorIn VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)


add_executable(DoorIn 
src/main.cpp
src/network/client.cpp
src/network/clientComHandler.cpp
src/network/server.cpp)

target_link_libraries(DoorIn Threads::Threads)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
