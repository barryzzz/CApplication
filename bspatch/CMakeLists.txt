

cmake_minimum_required(VERSION 3.4.1)
set(ANDROID_TOOLCHAIN gcc)

add_library(
             native-lib

             SHARED
             src/main/cpp/bspatch.h
             src/main/cpp/bspatch.c
             src/main/cpp/bzip2/bzlib.c
             src/main/cpp/bzip2/crctable.c
             src/main/cpp/bzip2/compress.c
             src/main/cpp/bzip2/decompress.c
             src/main/cpp/bzip2/randtable.c
             src/main/cpp/bzip2/blocksort.c
             src/main/cpp/bzip2/huffman.c
             src/main/cpp/native-lib.cpp )


find_library(
              log-lib

              log )



target_link_libraries(
                       native-lib


                       ${log-lib} )