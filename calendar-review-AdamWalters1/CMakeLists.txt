cmake_minimum_required(VERSION 3.28)
project(calendar)

set(CMAKE_CXX_STANDARD 14)

include_directories(cpp)

add_executable(calendar
        cpp/calendarType.h
        cpp/calendarTypeImp.cpp
        cpp/dateType.h
        cpp/dateTypeImp.cpp
        cpp/dayType.h
        cpp/dayTypeImp.cpp
        cpp/extDateType.h
        cpp/extDateTypeImp.cpp
        cpp/main.cpp)
