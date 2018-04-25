cmake_minimum_required(VERSION 3.4.1) #cmake 最小版本

set(libraryname native-lib)
set(list_one 1 2 3 4)
set(list_two "5;6;7;8")


add_library(
             ${libraryname}

             SHARED

             src/main/cpp/native-lib.cpp
             src/main/cpp/test.cpp
             src/main/cpp/simple.c
             src/main/cpp/testextrn.cpp
             src/main/cpp/cJSON.c
              )



find_library(
              log-lib

              log )


target_link_libraries(
                      ${libraryname}

                       ${log-lib} )

message(${libraryname})

message(${list_one})
message("${list_one}")

message(${list_two})
message("${list_two}")


set(if_tap ON)

if(${if_tap})
    message("这是if表达式")
endif(${if_tap})