cmake_minimum_required(VERSION 3.4)

project(v8LoadHttp)

add_library(v8LoadHttp STATIC
        src/http.cpp src/http.h
        src/LoadHttp.cpp include/v8LoadHttp/LoadHttp.h)

add_dependencies(v8LoadHttp AndriodWebsocket v8Core)

target_include_directories(v8LoadHttp include)

target_link_libraries(v8LoadHttp AndriodWebsocket v8Core)