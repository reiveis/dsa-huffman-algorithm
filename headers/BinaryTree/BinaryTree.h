#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <bitset>
#include "../Stack/PriorityStack.h"
#include "../HashMap/HashMap.h"

using namespace std;

class BinaryTree{
    private:
        string temp = "";
        PriorityStack<DATA> priorityStack;
        void generateCode(HashMap*, Node<DATA>*, bool);
    public:
        BinaryTree();
        void toStack(string);
        void makeTree();
        static Node<DATA>* makeTree(string);
        HashMap getCharMap();
};


BinaryTree::BinaryTree() {

}

void BinaryTree::toStack(string text) {
    PriorityStack<DATA> stack;
    for(int i=0; i<text.length(); i++){
        stack.push(text.at(i));
    }

    stack.display();

    priorityStack = stack;
}

void BinaryTree::makeTree() {
    while(priorityStack.getCount() > 1){
        srand(time(nullptr));
        Node<DATA>* p1 = priorityStack.pop();
        Node<DATA>* p2 = priorityStack.pop();


        Node<DATA>* pNew = new Node<DATA>;
        pNew->data = '\0';
        pNew->left = p1;
        pNew->right = p2;
        pNew->frequency = p1->frequency + p2->frequency;
        priorityStack.pushNode(pNew);
    }
    priorityStack.display();
}

Node<DATA>* BinaryTree::makeTree(string key){
    Node<DATA>* root = new Node<DATA>;
    root->left = nullptr;
    root->right = nullptr;
    Node<DATA>* pCurr = root;
    for(int i=0; i < key.length(); i++){
        Node<DATA>* pNew = new Node<DATA>;
        pNew->left = nullptr;
        pNew->right = nullptr;
        if(key.substr(i, 10) == "1101010010") {
            string temp = key.substr(i + 10, 8);
            bitset<8> bits{temp};

            unsigned char c = static_cast<unsigned char>(bits.to_ulong());
            //cout << "FOUND DATA " << c << endl;
            pCurr->data = c;
            pCurr = root;
            cout << "\t" << c << endl;
            i += 18;
            if(i>=key.length()) continue;
        }
        if(key.at(i) == '0'){
            if(pCurr->left == nullptr){
                cout << '0';
                pCurr->data = '\0';
                //cout << key.at(i) << " LEFT\n";
                pCurr->left = pNew;
                pCurr = pNew;
            }
            else{
                pCurr = pCurr->left;
            }
        }
        else if(key.at(i) == '1'){
            if(pCurr->right == nullptr){
                cout << '1';
                pCurr->data = '\0';
                //cout << key.at(i) << " RIGHT\n";
                pCurr->right = pNew;
                pCurr = pNew;
            }
            else{
                pCurr = pCurr->right;
            }
        }
//        else if(key.at(i) == '\\' && key.at(i+2) == '\\'){
//            cout << "FOUND DATA " << key.at(i+1) << endl;
//            pCurr->data = key.at(i+1);
//            pCurr = root;
//            i+=2;
//        }
    }
    return root;
}

HashMap BinaryTree::getCharMap() {
    HashMap codeMap;
    generateCode(&codeMap, priorityStack.peek(), true);
    return codeMap;
}


/**
 * Preorder traversal for binary tree, finding binary code for each character at the leaf node and stores it in a
 * Hash Map (Key-Value Pair)
 * @param map
 * @param root
 * @param isLeft
 */
void BinaryTree::generateCode(HashMap* map, Node<DATA>* root, bool isLeft) {
    if(root->right == nullptr && root->left == nullptr) {
        cout << root->data << " " << temp << endl;
        map->add(root->data, temp);

        //if(!isLeft) temp.pop_back();          // error
    }
    if (root->left != nullptr && root != nullptr) {
        temp+= "0";
        generateCode(map, root->left, true);
        temp.pop_back();
    }
    if (root->right != nullptr && root != nullptr) {
        temp+= "1";
        generateCode(map,root->right, false);
        temp.pop_back();
    }
}

#endif
