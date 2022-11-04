#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../BinaryTree/BinaryTree.h"
#include "../HashMap/HashMap.h"
#include <fstream>
#include <bitset>

/**
 * The Huffman Encoding and Decoding algorithms implement the binary tree structures as defined in BinaryTree.h
 *
 * The encode() function allows the program to input a string of text and have it be compressed to a huffman coding
 * format.
 */

class Huffman{
    private:
        HashMap* hashMap;
        string treeSearch(Node<DATA>*, Node<DATA>*, string bin);
    public:
        Huffman();
        string encode(string input);
        string decode(string binStr, string keyStr, int keyLength);

};

Huffman::Huffman() {

}

string Huffman::encode(string input) {
    srand(time(nullptr));
    string random = to_string(rand()%1000);

    BinaryTree huffmanTree;

    huffmanTree.toStack(input);
    huffmanTree.makeTree();
    HashMap characterMap = huffmanTree.getCharMap();

    string encodedOutput = "", output = "";

    string tableStream = characterMap.getTableStream();

    bitset<32> tableStreamLength(tableStream.length());

    for(int i=0; i<input.size(); i++){
        encodedOutput += characterMap.get(input.at(i));
    }

    bitset<32> outputStreamLength(encodedOutput.length());

    output += tableStreamLength.to_string() + outputStreamLength.to_string() + tableStream + encodedOutput;

    ofstream BinaryStream("../io/" + random + "binary.bin", ios::out | ios::binary);

    int i = 0;
    while(i<output.length()){
        bitset<8> bitChunk {output.substr(i, 8)};
        bitChunk <<= 8 - output.substr(i, 8).length();
        i+=8;
        BinaryStream.write(reinterpret_cast<char *>(&bitChunk), 1);
    }
    return output;
}

string Huffman::decode(string binStr, string keyStr, int keyLength) {
    string decodedOutput;

    Node<DATA>* huffmanTree = BinaryTree::makeTree(keyStr);
    cout << "DECODING... " << endl;
    decodedOutput += treeSearch(huffmanTree, huffmanTree, binStr);

    string fileName;
    cout << "\n\n\tEnter output file name\n\t>";
    cin >> fileName;
    ofstream OUTPUT ("../io/" + fileName, ios::out | ios::binary);

    OUTPUT << decodedOutput;

    OUTPUT.close();

    cout << "Binary file has been decompressed to \"" << fileName << "\"";

    return decodedOutput;
}

string Huffman::treeSearch(Node<DATA>* const origin, Node<DATA>* root, string bin) {
    string res = "";
    int i=0;
    while(i<bin.length()){
        if (bin.at(i) == '0' && root->left != nullptr) {
            root = root->left;
            i++;
        } else if (bin.at(i) == '1' && root->right != nullptr) {
            root = root->right;
            i++;
        }
        if (root->right == nullptr && root->left == nullptr) {
            res += root->data;
            root = origin;
            continue;
        }
    }
    return res;
}

#endif
