cmake_minimum_required(VERSION 3.8)
project(Vectah)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(SOURCE_FILES src/main.cpp src/Vectah.cpp src/IconArea.cpp src/Icon.cpp src/Icon.h)
set(HEADER_FILES src/Vectah.h src/IconArea.h src/Icon.cpp src/Icon.h)
add_executable(Vectah ${SOURCE_FILES} ${HEADER_FILES})

if (MSVC)
    # Force to always compile with W4
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif ()
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wno-parentheses")
endif ()

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK REQUIRED gtkmm-3.0)
include_directories(${GTK_INCLUDE_DIRS})
set(LIBS ${GTK_LIBRARIES})

pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
include_directories(${CAIROMM_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CAIROMM_LIBRARIES})

pkg_check_modules(LIBRSVG REQUIRED librsvg-2.0)
include_directories(${LIBRSVG_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LIBRSVG_LIBRARIES})

target_link_libraries(Vectah ${LIBS} stdc++fs)
