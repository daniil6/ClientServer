cmake_minimum_required(VERSION 3.10)

file(STRINGS "version" VERSION)

project(ClientServer VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(wxWidgets_LIB_DIR $ENV{WXWIN}/lib/gcc_libx64)

find_package(wxWidgets 3.2 REQUIRED xml core base)

include(${wxWidgets_USE_FILE})

include_directories(.)
include_directories($ENV{RBKLib}/include)

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_compile_options(-O0)
    add_compile_options(-Wall)
    add_compile_options(-Wextra)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES Release)
    add_link_options(-s)
endif()

add_link_options(-static)
add_link_options(-static-libgcc)
add_link_options(-static-libstdc++)

link_directories(${wxWidgets_LIB_DIR})
link_directories($ENV{RBKLib}/lib/gcc_libx64)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}-${CMAKE_BUILD_TYPE}-${PROJECT_VERSION}
)

target_sources(${PROJECT_NAME} PRIVATE rc/res.rc)
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_sources(${PROJECT_NAME} PRIVATE MainFrame.cpp)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

if (${CMAKE_BUILD_TYPE} MATCHES Release)
    target_link_libraries(${PROJECT_NAME} rbk)
endif()

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    target_link_libraries(${PROJECT_NAME} rbkd)
endif()

target_link_libraries(${PROJECT_NAME} ws2_32)