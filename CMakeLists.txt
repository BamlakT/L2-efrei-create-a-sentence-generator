cmake_minimum_required(VERSION 3.23)
project(dictionaryproject C)

set(CMAKE_C_STANDARD 99)

add_executable(dictionaryproject main.c "cmake-build-debug/tst node.c" "cmake-build-debug/LLD.c" "cmake-build-debug/LLD.h" "cmake-build-debug/tst node.h" cmake-build-debug/parser.c cmake-build-debug/parser.h cmake-build-debug/trie.c)
