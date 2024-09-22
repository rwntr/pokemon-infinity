cmake_minimum_required(VERSION 3.29)
project(pokemon_infinity C)
SET(CMAKE_MODULE_PATH ~/.CMakeModules)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")

FILE(GLOB_RECURSE SRCS asm/*.s data/*.s src/*.c constants/*.inc test/*.c tools/*.c data/*.inc)

ADD_EXECUTABLE(pokeemerald.gba ${SRCS})

TARGET_INCLUDE_DIRECTORIES(pokeemerald.gba PUBLIC BEFORE gflib)
TARGET_INCLUDE_DIRECTORIES(pokeemerald.gba PUBLIC BEFORE include)
TARGET_INCLUDE_DIRECTORIES(pokeemerald.gba PUBLIC BEFORE constants)
TARGET_INCLUDE_DIRECTORIES(pokeemerald.gba PUBLIC SYSTEM BEFORE tools/agbcc/include)


TARGET_COMPILE_DEFINITIONS(pokeemerald.gba PUBLIC __ARM_NONE_EABI_GCC__)