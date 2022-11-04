#ifndef MAP_NODE_H
#define MAP_NODE_H

#include "Data.h"
#include <iostream>
struct MapNode{
    MAP_KEY key;
    MAP_VALUE value;
    MapNode* link;
};

#endif
