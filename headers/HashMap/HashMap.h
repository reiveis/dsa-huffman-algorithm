#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include "MapNode.h"
#include "Data.h"

class HashMap{
    private:
        int count;
        MapNode* pHead;
        MapNode* pPre;
        string toASCII(char);

    public:
        HashMap();
        bool add(MAP_KEY key, MAP_VALUE value);
        bool addNode(MapNode*);
        MAP_VALUE get(MAP_KEY key);
        void display();
        void getEnd(MAP_KEY target);
        int size(){ return count; };
        string getTableStream();
};

HashMap::HashMap() {
    pHead = nullptr;
    pPre = nullptr;
    count = 0;
}

bool HashMap::add(MAP_KEY key, MAP_VALUE value) {
    try{
        MapNode *pNew = new MapNode;
        pNew->key = key;
        pNew->value = value;

        getEnd(key);
        if (pPre == nullptr) {
            pNew->link = pHead;
            pHead = pNew;
        } else {
            pNew->link = pPre->link;
            pPre->link = pNew;
        }
        count++;
        return true;
    }
    catch(std::bad_alloc &e){
        std::cerr << &e;
        return false;
    }
}

bool HashMap::addNode(MapNode* pNew){
    try{
        getEnd(pNew->key);
        if (pPre == nullptr) {
            pNew->link = pHead;
            pHead = pNew;
        } else {
            pNew->link = pPre->link;
            pPre->link = pNew;
        }
        count++;
        return true;
    }
    catch(std::bad_alloc &e) {
        std::cerr << &e;
        return false;
    }
}

MAP_VALUE HashMap::get(MAP_KEY key) {
    MapNode* pLoc = pHead;
    while(pLoc != nullptr){
        if(pLoc->key == key){
            return pLoc->value;
        }
        pLoc = pLoc->link;
    }
    return nullptr;
}

void HashMap::display() {
    MapNode* pWalk = pHead;
    while(pWalk != nullptr){
        std::cout << "MAP_KEY : " << pWalk->key << "\t\t" << pWalk->value << std::endl;
        pWalk = pWalk->link;
    }
}

void HashMap::getEnd(MAP_KEY target) {
    pPre = nullptr;
    MapNode* pLoc = pHead;
    while(pLoc != nullptr){
        pPre = pLoc;
        pLoc = pLoc->link;
    }
}

string HashMap::getTableStream() {
    MapNode *pLoc = pHead;
    string output = "";
    while(pLoc != nullptr){
        output += pLoc->value + "1101010010" + toASCII(pLoc->key);
        pLoc = pLoc->link;
    }

    return output;
}

string HashMap::toASCII(char c){
    string ASCII;
    for(int i=7; i>=0; i--){
        ASCII += to_string((c >> i) & 1);
    }
    return ASCII;
};

#endif
