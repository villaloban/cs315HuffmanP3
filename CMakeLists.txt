cmake_minimum_required(VERSION 3.28.1)
project(p3_part1)

set(CMAKE_CXX_STANDARD 20)

add_executable(p3_part1 main.cpp
        Scanner.cpp
        Scanner.hpp
        utils.cpp
        utils.hpp
        BinSearchTree.hpp
        PriorityQueue.hpp
        BinSearchTree.cpp
        TreeNode.hpp
        PriorityQueue.cpp
        HuffmanTree.cpp
        HuffmanTree.hpp
)
