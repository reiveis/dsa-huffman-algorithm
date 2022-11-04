#ifndef PRIORITY_STACK_H
#define PRIORITY_STACK_H

#include <iostream>
#include "Node.h"

using namespace std;

/**
 *  This priority stack is used to sort all DATA by its frequency in ascending order during insertion
 *  (whenever push() is called). It checks for the existence of the DATA that we want to insert, and if it does exist,
 *  then it will not push it onto the stack, instead it will only increment the frequency value by 1.
 *  then, if the frequency of that node is higher than the next node, we will swap places until a suitable node is found
 *  (once the current node is not higher than the next) using recursion (see swap()).
 *  \n
 *  This PriorityStack uses the Doubly-Linked List implementation of a stack, whereby each node has a forward and
 *  backward pointer.
 *  \n
 *  The base algorithms for this class were referred to in Blackboard (Stack, Stack, and Doubly-Linked List).
 *  \n
 *  The original code for this priority stack was intended to be a PriorityQueue,
 *  but there is a problem with calling it a queue as all elements inserted into it are inserted at the beginning,
 *  The elements can also be removed (pop()) at the beginning.
 *  Therefore the decision was made to call it a PriorityStack
 *
 */

template<typename X>
class PriorityStack{
private:
    //using Type = X;
    Node<X> *pTop;
    int count;
    Node<X> *pBottom;

public:
    int unique;

    Node<X>* peek(){
        return pTop;
    }

    PriorityStack() {
        pTop = nullptr;
        pBottom = nullptr;
        count = 0;
    }

    int getCount(){
        return count;
    }

/**
 * Push a new node onto the PriorityStack, it will always insert the node at the beginning (or top)
 * @param dataIn
 * @return
 */
    bool push(DATA dataIn) {
        try{
            Node<X> *pNew = new Node<X>();
            Node<X>* x;
            if((x = search(dataIn)) != nullptr && x->left == nullptr && x->right == nullptr) {
                //cout << "FOUND " << '\'' << x->data << '\'' << endl;
                x->frequency++;

                if(x->forward != nullptr && x->frequency >= x->forward->frequency){
                    swap(x,x->forward);
                }
            }
            else {
                pNew->data = dataIn;
                pNew->forward = nullptr;

                if (count == 0) {
                    pNew->backward = nullptr;
                    pTop = pNew;
                    pBottom = pTop;
                } else {
                    pNew->forward = pTop;
                    pNew->backward = nullptr;
                    pTop->backward = pNew;
                    pTop = pNew;
                }
                count++;
                unique++;
                return true;
            }

        }
        catch(bad_alloc& e){    // if there is no memory left to allocate another node, return false
            cerr << "Out of memory error";
            return false;
        }
        return true;
    }

    bool pushNode(Node<X>* nodeIn){
        nodeIn->forward = nullptr;

        if (count == 0) {
            nodeIn->backward = nullptr;
            pTop = nodeIn;
            pBottom = pTop;
        } else {
            nodeIn->forward = pTop;
            nodeIn->backward = nullptr;
            pTop->backward = nodeIn;
            pTop = nodeIn;
        }
        count++;
        //cout << "ADDED : " << nodeIn->data << endl;

        if(nodeIn->forward != nullptr && nodeIn->frequency >= nodeIn->forward->frequency){
            swap(nodeIn,nodeIn->forward);
        }

        return true;
    }

    Node<X>* pop() {
        if(count == 0){
            return nullptr;
        }

        Node<X>* pLoc = pTop;

        if(count == 1){
            pBottom = nullptr;
        }
        pTop = pTop->forward;
        count--;

        return pLoc;
    }

    bool stackTop(DATA *dataOut) {
        if(count == 0){
            return false;
        }
        *dataOut = pTop->data;
        return true;
    }

    bool stackBottom(DATA *dataOut) {
        if(count == 0){
            return false;
        }
        *dataOut = pBottom->data;
        return true;
    }

    Node<X> *search(DATA target) {
        Node<X>* pLoc = pTop;

        while(pLoc != nullptr){
            if(pLoc->data == target){
                return pLoc;
            }
            pLoc = pLoc->forward;
        }
        return nullptr;
    }

    void swap(Node<X> *x, Node<X> *y) {
        //cout << "SWAP CALLED ON \'" << x->data << '\'' << endl;
        /**
         * Swap two nodes together with their corresponding backwards and forwards pointers
         */
//    Node* temp = x;
//    // if y has no forward node
//    x->forward = (y->forward == nullptr) ? new Node() : y->forward;
//    y->forward = x;
//    x->backward->forward = y;
//    x->backward = y;
//    y->backward = x->backward;
//    y->forward->backward = x;

        Node<X>* temp1 = x->backward;
        Node<X>* temp2 = y->forward;
        if(temp1 != nullptr){
            // if x is NOT the front of the stack (x has a null backwards pointer)
            temp1->forward = y;
        }
        else{
            // make y the front node
            pTop = y;
        }
        if(temp2 != nullptr){
            // if y is NOT the rear of the stack, (y has a null forwards pointer)
            temp2->backward = x;
        }
        else{
            // make x the rear node
            pBottom = x;
        }
        x->backward = y;
        x->forward = y->forward;
        y->backward = temp1;
        y->forward = x;

        // if the frequency is still not sorted, keep swapping
        if(x->forward != nullptr && x->frequency >= x->forward->frequency){
            swap(x, x->forward);
        }

    }

    void display(){
        Node<X>* pWalk = pTop;

        cout << endl << "\t[ STACK CONTENTS ]" << endl;
        while(pWalk != nullptr) {
            cout
                    << "\tDATA: "
                    << '\'' << pWalk->data << '\''
                    << "\t\tFREQUENCY: "
                    << pWalk->frequency
                    << endl;
            pWalk = pWalk->forward;
        }
        cout << endl;
    }
};

#endif