cmake_minimum_required(VERSION 3.18.1)
project("myapplicationndk")
# 定义变量 SOURCE
file(GLOB SOURCE *.cpp *.c)

include_directories(${CMAKE_SOURCE_DIR}/inc)

add_library(myapplicationndk
        STATIC
        ${SOURCE}
        )

find_library(log-lib log)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libs")

# add_library(avutil STATIC IMPORTED)
# set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/libs/libavutil.a)

# 链接log到主库
target_link_libraries(myapplicationndk
        ${log-lib}
        )

message("SATUS here")

