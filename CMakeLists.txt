cmake_minimum_required(VERSION 3.14)
project(vision)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-static-libstdc++")

message( STATUS "Profile: ${PROFILE}" )

if ("${PROFILE}" STREQUAL "macos")
    include_directories(
            /usr/local/include/opencv4
    )
    link_directories(
            /usr/local/lib
            /usr/local/lib/opencv4/3rdparty
    )
elseif ("${PROFILE}" STREQUAL "arm")
    include_directories(
            ../opencv-arm/build/install/include/opencv4
    )
    link_directories(
            ../opencv-arm/build/install/lib
            ../opencv-arm/build/install/lib/opencv4/3rdparty
    )
else()
    message( ERROR "unsupported build profile" )
    return()
endif()

add_executable(vision main.cpp)

target_link_libraries(
        vision
        # video
        opencv_videoio
        opencv_video
        # gui
        opencv_highgui
        # image processing
        opencv_imgcodecs
        opencv_imgproc
        opencv_core
        libjpeg-turbo
        libjasper
        libtiff
        libpng
        libwebp
        ittnotify
        dl
        z
)

if ("${PROFILE}" STREQUAL "arm")
    target_link_libraries(
            vision
            tegra_hal
            pthread
    )
endif()
