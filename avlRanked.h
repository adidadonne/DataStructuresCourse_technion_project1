
#ifndef WET1SUMMER_AVLRANKED_H
#define WET1SUMMER_AVLRANKED_H

#include "avlRankedNode.h"
#include <math.h>
#include <iostream>
#include <stdexcept>
using std::exception;
using namespace std;

class avlRanked {

private:
    avlRankedNode* root_;
    int size_;


public:
    class IDAlreadyExists : public exception {
    public :
        const char* what() const noexcept override { return "ID already exists in tree"; }
    };

    class IDNotExists : public exception {
    public :
        const char* what() const noexcept override { return "ID not exists in tree"; }
    };

    class allocationError : public exception {
    public :
        const char* what() const noexcept override { return "Memory allocation error"; }
    };
    avlRankedNode *minNode_;
    avlRanked();
    ~avlRanked();
    void deleteTree( avlRankedNode* node ) ;
    avlRankedNode *getRoot() ;

    avlRankedNode* findNode(avlRankedNode* root ,int key) ;
    void insertNode( ImageTreeData* data, int key );
    avlRankedNode* insertNodeAux( avlRankedNode* root , avlRankedNode* newNode, int key);
    avlRankedNode* removeNode(avlRankedNode* root , int key);
    avlRankedNode* findMax(avlRankedNode* root);
    void swap(avlRankedNode* A, avlRankedNode * B);
    int checkHeight( avlRankedNode* root) ;
    int findHeight( avlRankedNode* root) ;
    int findBalance( avlRankedNode* root) ;


    avlRankedNode* leftRotation(avlRankedNode* node);
    avlRankedNode* rightRotation(avlRankedNode* node);

    void printTest(avlRankedNode* root);
    void cleantree();
    avlRankedNode* climb(int m);
    int getsize();
    bool isEmpty();

    avlRankedNode* select(avlRankedNode* root, int k);

};



#endif //WET1SUMMER_AVLRANKED_H
