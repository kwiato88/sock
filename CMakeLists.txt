cmake_minimum_required(VERSION 2.8)

project(Sock)

include_directories(
    Include
    D:/boost_1_61_0
    D:/googletest-release-1.6.0/include
    D:/googlemock-release-1.6.0/include
)

link_directories(
    D:/boost_1_61_0/stage/lib
    D:/googletest-release-1.6.0/Build/Debug
    D:/googlemock-release-1.6.0/Build/Debug
)

add_library(
    libSock
    STATIC
    Source/SockBaseSocket.cpp
    Source/SockClientSocket.cpp
    Source/SockListeningSocket.cpp
    Source/SockSocketUtils.cpp
    Source/SockSocketError.cpp
)

add_executable(
    ServerEx
    Source/SerwerMain.cpp
)

target_link_libraries(
    ServerEx
    libSock
    ws2_32
)

add_executable(
    ClientEx
    Source/ClientMain.cpp
)

target_link_libraries(
    ClientEx
    libSock
    ws2_32
)

if( MSVC ) # VS2012 doesn't support correctly the tuples yet
    add_definitions( /D _VARIADIC_MAX=10 )
endif()
