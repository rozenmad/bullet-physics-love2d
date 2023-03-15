# Minimum cmake version required
cmake_minimum_required(VERSION 3.8)

# Project
project(love_bullet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# expected behaviour
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++lastest")

set(BUILD_ENET OFF CACHE BOOL "disable ENET")
set(BUILD_CLSOCKET OFF CACHE BOOL "disable CLSOCKET")
set(USE_GRAPHICAL_BENCHMARK OFF CACHE BOOL "disable GRAPHICAL_BENCHMARK")
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "disable OPENGL3_DEMOS")
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "disable BULLET2_DEMOS")
set(BUILD_CPU_DEMOS OFF CACHE BOOL "disable CPU_DEMOS")
set(BUILD_EGL OFF CACHE BOOL "disable EGL")
set(USE_GLUT OFF CACHE BOOL "disable GLUT")
set(BUILD_UNIT_TESTS OFF CACHE BOOL "disable UNIT_TESTS")
set(BUILD_EXTRAS OFF CACHE BOOL "disable EXTRAS")
set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "disable MSVC_RUNTIME_LIBRARY_DLL")
add_subdirectory(bullet3)

find_package(Lua)
include_directories(${LUA_INCLUDE_DIR})
include_directories(bullet3/src/)

file(GLOB bt
    "bt/*.h"
    "bt/*.cpp"
    "bt/shapes/*.h"
    "bt/shapes/*.cpp"
    "bt/callback/*.h"
    "bt/callback/*.cpp"
)

set(WRAPPER_INCLUDE
    love_luapi/config.h
    love_luapi/Exception.h
    love_luapi/int.h
    love_luapi/Module.h
    love_luapi/Object.h
    love_luapi/Reference.h
    love_luapi/runtime.h
    love_luapi/StringMap.h
    love_luapi/types.h
    love_luapi/Variant.h
    love_bullet.h
)

set(WRAPPER_SOURCES
    love_luapi/Exception.cpp
    love_luapi/Module.cpp
    love_luapi/Object.cpp
    love_luapi/Reference.cpp
    love_luapi/runtime.cpp
    love_luapi/StringMap.cpp
    love_luapi/types.cpp
    love_luapi/Variant.cpp
    love_bullet.cpp
)

find_library(lua51 lua51)

# Create the library
add_library(love_bullet SHARED ${bt} ${WRAPPER_INCLUDE} ${WRAPPER_SOURCES})

target_link_libraries(love_bullet ${LUA_LIBRARIES} 
    Bullet2FileLoader Bullet3Collision 
    Bullet3Common Bullet3Dynamics Bullet3Geometry BulletCollision BulletDynamics 
    BulletInverseDynamics BulletSoftBody LinearMath)