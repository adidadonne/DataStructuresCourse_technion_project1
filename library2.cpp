#include "library2.h"
#include "ImageTagger.h"

void *Init(int segments)
{
    ImageTagger * DS;
    try
    {

        DS = new ImageTagger(segments);
    }
    catch (std::bad_alloc &e)
    {
        return NULL;
    }
    return (void*)DS;
}

StatusType AddImage(void *DS, int imageID)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        return ((ImageTagger*)DS)->AddImage(imageID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType DeleteImage(void *DS, int imageID)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        return ((ImageTagger*)DS)->DeleteImage(imageID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType AddLabel(void *DS, int imageID, int segmentID, int label)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        return ((ImageTagger*)DS)->AddLabel(imageID,segmentID,label);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}
StatusType GetLabel(void *DS, int imageID, int segmentID, int *label)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        return ((ImageTagger*)DS)->GetLabel(imageID,segmentID,label);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType DeleteLabel(void *DS, int imageID, int segmentID)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        return ((ImageTagger*)DS)->DeleteLabel(imageID,segmentID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments, int *numOfSegments)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        return ((ImageTagger*)DS)->GetAllUnlabeledSegments(imageID,segments,numOfSegments);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}

StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int *numOfSegments)
{
    if(DS==NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        return ((ImageTagger*)DS)->GetAllSegmentsByLabel(label,images,segments,numOfSegments);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
}
void Quit(void** DS)
{
    if (DS==NULL) return;
    delete ((ImageTagger*) *DS);
    *DS=NULL;
}