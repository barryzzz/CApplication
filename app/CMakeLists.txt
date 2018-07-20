cmake_minimum_required(VERSION 3.4.1) #cmake 最小版本

set(libraryname diff)
set(list_one 1 2 3 4)
set(list_two "5;6;7;8")

#so输出的路径
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI})






add_library(
             ${libraryname}

             SHARED

              src/main/cpp/native-lib.cpp
              src/main/cpp/test.cpp
              src/main/cpp/simple.c
              src/main/cpp/testextrn.cpp
              src/main/cpp/cJSON.c
              src/main/cpp/native-lib.cpp
              src/main/cpp/bspatch.c
              src/main/cpp/bzip2/bzlib.c
              src/main/cpp/bzip2/crctable.c
              src/main/cpp/bzip2/compress.c
              src/main/cpp/bzip2/decompress.c
              src/main/cpp/bzip2/randtable.c
              src/main/cpp/bzip2/blocksort.c
              src/main/cpp/bzip2/huffman.c
              src/main/cpp/bspatch.h

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