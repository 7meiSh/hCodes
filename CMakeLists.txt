cmake_minimum_required(VERSION 3.24)
project(Hcodes C)

set(CMAKE_C_STANDARD 90)

add_executable(Hcodes main.c freqTable.h freqTable.c buildTree.h buildTree.c generateCodes.c encodER.h encodER.c encode.h encode.c decodER.c decodER.h decode.c decode.h)
