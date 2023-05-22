

#ifndef WET1SUMMER_LISTNODE_H
#define WET1SUMMER_LISTNODE_H
#include <iostream>
using namespace std;

#include "Image_data.h"

class listNode
    {

public:
    int key;
    Image_data* element;
    listNode* prev;
    listNode* next;

    listNode() : key(), element(nullptr), prev(nullptr), next(nullptr){};
    listNode(int key, Image_data* element, listNode* prev = nullptr, listNode* next = nullptr) : key(key), element(element), prev(prev), next(next) {};
    ~listNode()
    {
        delete element;
    }
};

#endif //WET1SUMMER_LISTNODE_H
