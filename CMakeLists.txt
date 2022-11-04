cmake_minimum_required(VERSION 3.23)
project(DSA_FINAL_HUFFMAN)

set(CMAKE_CXX_STANDARD 14)

add_executable(DSA_FINAL_HUFFMAN HuffmanCoding.cpp headers/Data.h headers/Stack/Node.h headers/Stack/PriorityStack.h headers/BinaryTree/BinaryTree.h headers/Huffman/Huffman.h headers/HashMap/HashMap.h headers/HashMap/MapNode.h headers/HashMap/Data.h)
