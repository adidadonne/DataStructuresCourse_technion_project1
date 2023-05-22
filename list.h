

#ifndef WET1SUMMER_LIST_H
#define WET1SUMMER_LIST_H
#include "listNode.h"
#include <iostream>
using namespace std;

//template <class T>
class list {
private:
    listNode* head;
    listNode* tail;
    int size;

public:
    list()
    {
        head = new listNode();
        if ( head == nullptr )
        {
            throw allocationError();
        }
        tail = head;
        size = 0;
    }

    list(int key, Image_data* element); // constructor
    list (list &l);
    ~list();


    listNode *getHead() ;
    listNode *getTail() ;
    void setTail(listNode *tail);
    void insertLast(int key, Image_data* element);
    void insertNode(listNode *currentNode, int key, Image_data* element);
    void removeNode( listNode* currentNode); //Removing Node from the list
    listNode* popNode(listNode *currentNode);
    bool isEmpty();
    listNode* find(int key) ;
    int getSize();
    class allocationError : public exception {
    public :
        const char* what() const noexcept override { return "Memory allocation error"; }
    };

};

#endif //WET1SUMMER_LIST_H
