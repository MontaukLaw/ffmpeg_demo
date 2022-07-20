# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# 关键性的CMakeLists, 这个是起点, 其他都是孙子
# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("myapplicationndk")
file(GLOB SOURCE ${CMAKE_SOURCE_DIR}/cpp/*.cpp ${CMAKE_SOURCE_DIR}/cpp/*.c)

add_library(myapplicationndk
        SHARED
        # ${SOURCE}
        ${CMAKE_SOURCE_DIR}/cpp/native-lib.cpp
        ${CMAKE_SOURCE_DIR}/cpp/JNICallBackHelper.cpp
        ${CMAKE_SOURCE_DIR}/cpp/MarcsPlayerCPP.cpp
        ${CMAKE_SOURCE_DIR}/cpp/VideoChannel.cpp
        ${CMAKE_SOURCE_DIR}/cpp/AudioChannel.cpp
        )
## 第一步, 导入头文件
#include_directories("${CMAKE_SOURCE_DIR}/cpp/inc")
##第二步, 导入库文件(方式一)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/jnilibs/${CMAKE_ANDROID_ARCH_ABI}")
##第三步 连接到总库当中去
#target_link_libraries( # Specifies the target library.
#        myapplicationndk
#        # Links the target library to the log library
#        # included in the NDK.
#        log   # 获取上面的库文件, 也可以直接写链接库的名字
#        fmod
#        fmodL
#        )

# 第二种方法:
# 第一步, 导入头文件
include_directories("${CMAKE_SOURCE_DIR}/cpp/inc")

# 第二步, 导入库文件(方式二)
add_library(fmod SHARED IMPORTED)
set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libfmod.so)

# 有更多的库就重复导入多次

# 两种方法都可以.

# 使用开关来切换生成静态/动态库
set(isSTATIC ON)
if (${isSTATIC})
    add_library(getndk STATIC IMPORTED)
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libgetndk.so)
    message("Using STATIC lib")

else (${isSTATIC})
    add_library(getndk SHARED IMPORTED)
    set_target_properties(fmod PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libgetndk.a)
    message("Using shared lib")

endif (${isSTATIC})

#target_link_libraries( # Specifies the target library.
#        myapplicationndk
#        # Links the target library to the log library
#        # included in the NDK.
#        log   # 获取上面的库文件, 也可以直接写链接库的名字
#        fmod
#        fmodL
#        getndk # 这个库的具体引用方法, 可以看上面的切换部分
#        )

# main库进行连接libget.a
# 进入libget目录查找CM艾克Lists.txt里面的配置
add_subdirectory(${CMAKE_SOURCE_DIR}/cpp/libget)

add_subdirectory(${CMAKE_SOURCE_DIR}/cpp/libcppcount)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}")

target_link_libraries(
        myapplicationndk
        get
        counter
        log
        # 忽略顺序的方式，导入
        -Wl,--start-group
        avcodec avfilter avformat avutil swresample swscale
        -Wl,--end-group
        z
        rtmp
        android
        OpenSLES
)