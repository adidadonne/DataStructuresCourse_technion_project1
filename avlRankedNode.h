

#ifndef WET1SUMMER_AVLRANKEDNODE_H
#define WET1SUMMER_AVLRANKEDNODE_H

#include <math.h>
#include <iostream>
#include <stdexcept>

#include "ImageTreeData.h"

using std::exception;
using namespace std;

class avlRankedNode{
public:

    int key;
    ImageTreeData* data_ ;
    avlRankedNode *parent_ = nullptr;
    avlRankedNode *left_ = nullptr;
    avlRankedNode *right_ = nullptr;
    int height;
    int w;

    avlRankedNode()= default;
    avlRankedNode(ImageTreeData* data, int key): key(key), data_(data), parent_(nullptr), left_(nullptr),
                                  right_(nullptr), height(0), w(1) {};
    ~avlRankedNode() {
        if (data_ != nullptr)
        {
            delete data_;
        }
//        if (key != nullptr) { ////TODO: We know that the key in our use is the same as the data, so we don't need to delete it.
//            delete key;
//        }
    };

};



#endif //WET1SUMMER_AVLRANKEDNODE_H
