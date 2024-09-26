cmake_minimum_required(VERSION 3.0)

project(Sock)

link_directories(
    C:/Users/pikwiatk/boost_1_61_0/binMsvc
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
    Source/SockAddr.cpp
    Source/SockSocketError.cpp
    Source/SockConnection.cpp
    Source/SockServer.cpp
)

target_include_directories(
    libSock
    PUBLIC
    Include
    C:/Users/pikwiatk/boost_1_85_0
    C:/Users/pikwiatk/googletest-release-1.6.0/include
    C:/Users/pikwiatk/googlemock-release-1.6.0/include
)

add_executable(
    ServerEx
    Source/SerwerMain.cpp
)

target_include_directories(
    ServerEx
    PUBLIC
    Include
    C:/Users/pikwiatk/boost_1_85_0
#    C:/Users/pikwiatk/googletest-release-1.6.0/include
#    C:/Users/pikwiatk/googlemock-release-1.6.0/include
)

add_dependencies(
    ServerEx
    libSock
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

target_include_directories(
    ClientEx
    PUBLIC
    Include
    C:/Users/pikwiatk/boost_1_85_0
#    C:/Users/pikwiatk/googletest-release-1.6.0/include
#    C:/Users/pikwiatk/googlemock-release-1.6.0/include
)

add_dependencies(
    ClientEx
    libSock
)

target_link_libraries(
    ClientEx
    libSock
    ws2_32
)

if( MSVC ) # VS2012 doesn't support correctly the tuples yet
    add_definitions( /D _VARIADIC_MAX=10 )
endif()
