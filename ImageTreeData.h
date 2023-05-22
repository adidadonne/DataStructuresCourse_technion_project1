
#ifndef WET1SUMMER_IMAGETREEDATA_H
#define WET1SUMMER_IMAGETREEDATA_H
#include "list.h"
#include <iostream>
#include <memory>
class ImageTreeData
{
    friend class ImageTagger;
private:
    //// smart ptr and struct array?///
    int size;
    list* unlabeled_list;
    listNode** label_array;
    list* labeled_list;

public:
    ImageTreeData(): size(0), unlabeled_list(nullptr), label_array(nullptr), labeled_list(nullptr){};
    explicit ImageTreeData(int segment)
    {
        size=segment;
        unlabeled_list=new list();
        label_array = new listNode*[segment];
        labeled_list=new list();
    }
    /* ImageTreeData (ImageTreeData& t)
     {
         size=t.size;
         unlabeled_list = t.unlabeled_list;
         labeled_list= t.labeled_list;
         delete [] label_array;
         label_array= new listNode<Image_data>*[size];
     }*/
    //ImageTreeData& operator=(ImageTreeData& t);
    ~ImageTreeData()
    {
        if ( label_array!=NULL)
        {
//            for(int i=0; i<size;i++)
//            {
//                if( label_array[i]!=NULL && label_array[i]->element->label==-1 )
//                {
//                    unlabeled_list->removeNode(label_array[i]);
//                    label_array[i]=NULL;
//                }
//                else if (label_array[i]!=NULL)
//                {
//                    labeled_list->removeNode(label_array[i]);
//                    label_array[i]=NULL;
//                }
//            }
            delete[] label_array;
            //label_array= nullptr;
        }
        if (unlabeled_list!= NULL)
        {
           // unlabeled_list->~list();
            delete unlabeled_list;
            //unlabeled_list= nullptr;
        }
        if (labeled_list!=NULL)
        {
           // labeled_list->~list();
            delete labeled_list;
            //labeled_list= nullptr;
        }


    }
};




#endif //WET1SUMMER_IMAGETREEDATA_H
