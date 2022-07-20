cmake_minimum_required(VERSION 3.18.1)
# 这个文件的内容跟之前做cpp编译是一样的.
set(CMAKE_CXX_STANDARD 14)

file(GLOB CSOURCE *.cpp)   # 将所有的c文件组织成一个组合

add_library(
        counter  # 最后生成的库名
        STATIC # 告诉编译器, 生成静态库
        ${CSOURCE}  # 使用变量代替所有源文件名
)
