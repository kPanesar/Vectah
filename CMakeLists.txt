cmake_minimum_required(VERSION 3.8)
project(Vectah)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(SOURCE_FILES main.cpp)
add_executable(Vecto ${SOURCE_FILES})

if (MSVC)
    # Force to always compile with W4
    if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif ()
elseif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
endif ()

find_package(Cairomm REQUIRED)
if (CAIROMM_FOUND)
    include_directories(${CAIROMM_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${CAIROMM_LIBRARIES})
else (CAIROMM_FOUND)
    message(FATAL_ERROR "Cairomm not found! Please make sure it is installed.")
endif (CAIROMM_FOUND)

find_package(Poppler REQUIRED)
if (POPPLER_FOUND)
    include_directories(${POPPLER_INCLUDE_DIRS})
    set(LIBS ${LIBS} ${POPPLER_LIBRARIES})
else (POPPLER_FOUND)
    message(FATAL_ERROR "Poppler not found! Please make sure it is installed.")
endif (POPPLER_FOUND)

target_link_libraries(Vecto ${LIBS})
