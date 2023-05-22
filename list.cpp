

#include "list.h"

//template<class T>
list::list(int key, Image_data* element) {
    head = new listNode(key, element);
    if ( head == nullptr ){
        throw allocationError();
    }
    tail = head;
    size = 0;
}

//template<class T>
list::~list() {

    listNode* tmpHead;
    tail = nullptr;
    while(head != nullptr)
    {
        tmpHead = this->head->next;
        delete head;
        head = tmpHead;
    }
}

//template<class T>
list::list(list &l)
{
    listNode dummy;
    for (listNode* it=l.head, *n=&dummy, *p=NULL;  it; it=it->next) {
        n->next=new listNode(it->key,it->element);
        n->prev=p;
        p=n;
        n=n->next;
        if(it->next==NULL)
        {
            tail=n->next;
        }
    }
    head=dummy.next;
}

//template<class T>
listNode *list::getHead()
{
    return head;
}

//template<class T>
listNode *list::getTail()
{
    return tail;
}

//template<class T>
void list::setTail(listNode *tail)
{
    list::tail = tail;
}

//template<class T>
void list::insertLast(int key, Image_data* element)
{
    listNode* newNode = new listNode(key, element,tail, NULL);
    if( !newNode )
    {
        throw allocationError();
    }
    tail->next=newNode;
    tail=newNode;
    size++;
}

// Inserting the wanted node as the next node.
//template<class T>
void list::insertNode(listNode *currentNode, int key, Image_data* element)
{
    if(!currentNode)
    {
        return;
    }
    listNode* newNode = new listNode(key, element, currentNode, currentNode->next);
    if( !newNode )
    {
        throw allocationError();
    }
    if (currentNode->next)
    {
        currentNode->next->prev = newNode;
    }
    currentNode->next = newNode;

    if(tail == currentNode)
    {
        tail = newNode;
    }
    size++;
}

//template<class T>
void list::removeNode( listNode *currentNode)
{
    if(!currentNode)
    {
        return;
    }
    if (currentNode->next)
    {
        currentNode->next->prev = currentNode->prev;
    }
    currentNode->prev->next = currentNode->next;

    if(currentNode == tail)
    {
        tail = tail->prev;
    }
    delete currentNode;
//    *currentNode = nullptr;
    size--;
}

//template<class T>
listNode *list::popNode(listNode *currentNode) {
    if(!currentNode)
    {
        return nullptr;
    }
    if (currentNode->next){
        currentNode->next->prev = currentNode->prev;
    }
    currentNode->prev->next = currentNode->next;

    if(currentNode == tail)
    {
        tail = tail->prev;
    }
    return currentNode;
}

//template<class T>
bool list::isEmpty()
{
    return head == tail;
}

//template<class T>
listNode *list::find(int key)
{
    listNode* tmp = head;
    while(tmp != nullptr)
    {
        if (tmp->key == key)
        {
            return tmp;
        }
        tmp=tmp->next;
    }
    return nullptr;
}

//template<class T>
int list::getSize()
{
    return size;
}