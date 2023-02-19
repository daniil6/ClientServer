cmake_minimum_required(VERSION 3.25)

project(ClientServer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(wxWidgets_LIB_DIR $ENV{WXWIN}/lib/gcc_libx64)

find_package(wxWidgets 3.1 REQUIRED propgrid xml core base)

include(${wxWidgets_USE_FILE})


include_directories(.)
include_directories($ENV{RBKLib}/include)
#include_directories(link)

message($ENV{RBKLib}/include)

add_link_options(-static)
add_link_options(-static-libgcc)
add_link_options(-static-libstdc++)

link_directories(${wxWidgets_LIB_DIR})
link_directories($ENV{RBKLib}/lib/gcc_libx64)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME invest-${CMAKE_BUILD_TYPE}-${PROJECT_VERSION}
        )

target_sources(${PROJECT_NAME} PRIVATE  main.cpp)
target_sources(${PROJECT_NAME} PRIVATE  MainFrame.cpp)
target_sources(${PROJECT_NAME} PRIVATE  link/baselink.cpp)
#target_sources(${PROJECT_NAME} PRIVATE  link/tcpclient.cpp)
target_sources(${PROJECT_NAME} PRIVATE  link/tcpprocess.cpp)
#target_sources(${PROJECT_NAME} PRIVATE  link/tcpserver.cpp)
target_sources(${PROJECT_NAME} PRIVATE  link/udpclient.cpp)
target_sources(${PROJECT_NAME} PRIVATE  link/udpprocess.cpp)
target_sources(${PROJECT_NAME} PRIVATE  link/udpserver.cpp)

target_link_libraries(${PROJECT_NAME} rbk)

#target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
include(D:/YandexDisk/solve/build/wx-library.cmake)
