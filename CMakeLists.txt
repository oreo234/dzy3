cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        class.h
        buyer.h
        member.h
        honoured_guest.h
        book.h
        layfolk.h
        order.h
        global.h)
