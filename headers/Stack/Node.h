#ifndef NODE_H
#define NODE_H

#include "../Data.h"

template <typename T>
class Node {
public:
    KEY frequency = 1;
    T data = '\0';

    Node* forward;
    Node* backward;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(){

    }
    Node(int frequency) {
        this->frequency = frequency;
        this->left = nullptr;
        this->right = nullptr;
    }
};



#endif