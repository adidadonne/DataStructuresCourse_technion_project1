
#ifndef WET1SUMMER_IMAGETAGGER_H
#define WET1SUMMER_IMAGETAGGER_H
#include "library2.h"
#include "avlRanked.h"
#include <iostream>
#include <memory>
class ImageTagger {

private:
    int segment;
    avlRanked* image_tree;

    void inorder_count(avlRankedNode* p , int& counter , int label);
    void inorder_update(avlRankedNode *p,int& index, int label, int*&images, int*&segments) ;
public:
    ImageTagger (int seg);
    //ImageTagger(int segment, avlRanked<ImageTreeData,int> image_tree):segment(segment), image_tree(image_tree){};
    ImageTagger(ImageTagger& i)=default;
    ImageTagger& operator=(ImageTagger& i)=default;
    ~ImageTagger()
    {
        delete image_tree;
    }
    StatusType AddImage(int imageID);
    StatusType DeleteImage(int imageID);
    StatusType AddLabel(int imageID, int segmentID, int label);
    StatusType GetLabel(int imageID, int segmentID, int* label);
    StatusType DeleteLabel(int imageID, int segmentID);
    StatusType GetAllUnlabeledSegments(int imageID, int** segments, int* numOfSegments );
    StatusType GetAllSegmentsByLabel(int label, int** images, int**segments, int* numOfSegments);

};


#endif //WET1SUMMER_IMAGETAGGER_H
