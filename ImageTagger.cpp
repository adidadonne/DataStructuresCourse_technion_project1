#include "ImageTagger.h"

ImageTagger::ImageTagger(int seg)
{
    segment = seg;
    image_tree = new avlRanked();
}

StatusType ImageTagger::AddImage(int imageID)
{
    if(imageID<0 || imageID==0)
    {
        return INVALID_INPUT;
    }
    /// if image tree already exist in tree than we will return failure
    if(image_tree->findNode(image_tree->getRoot(),imageID)!=nullptr)
    {
        return FAILURE;
    }
    /// we will add a new node to the tree
   // ImageTreeData* data= new ImageTreeData(segment);
    image_tree->insertNode(new ImageTreeData(segment),imageID);
    /// saving ptr for the node we just added to the tree
    avlRankedNode* image_ptr =  image_tree->findNode(image_tree->getRoot(),imageID);
    /// going over the array,
    /// adding nodes to the unlabeled list
    /// and updating ptrs to then in the array
    for(int i=0;i<segment;i++)
    {
        //Image_data* data= new Image_data(imageID,i,-1);
        image_ptr->data_->unlabeled_list->insertLast(imageID,new Image_data(imageID,i,-1));
        image_ptr->data_->label_array[i]= image_ptr->data_->unlabeled_list->getTail();
    }
    return SUCCESS;
}

StatusType ImageTagger::DeleteImage(int imageID)
{
    if(imageID<0 || imageID==0)
    {
        return INVALID_INPUT;
    }
    /// checking if this imageID exist in this tree, if *not* we will return failure
    if(image_tree->findNode(image_tree->getRoot(),imageID)==nullptr)
    {
        return FAILURE;
    }
    /// we will save ptr for this image node
    avlRankedNode* image_ptr =  image_tree->findNode(image_tree->getRoot(),imageID);
    for(int i=0; i<segment;i++)
    {
        if( image_ptr->data_->label_array[i]->element->label==-1 )
        {
            image_ptr->data_->unlabeled_list->removeNode(image_ptr->data_->label_array[i]);
           // image_ptr->data_->label_array[i]=NULL;
            //delete image_ptr->data_->label_array[i];
        }
        else
        {
            image_ptr->data_->labeled_list->removeNode(image_ptr->data_->label_array[i]);
           // image_ptr->data_->label_array[i]=NULL;
            //delete image_ptr->data_->label_array[i];
        }
    }
    /// imageTreeData destructor will delete the array
    /// lists destructors will delete the lists
    image_tree->removeNode(image_tree->getRoot(),imageID);
    return SUCCESS;
}


StatusType ImageTagger::AddLabel(int imageID, int segmentID, int label)
{
    if(segmentID > segment || segmentID ==segment || segmentID <0)
    {
        return INVALID_INPUT;
    }
    if(imageID<0 || imageID==0)
    {
        return INVALID_INPUT;
    }
    if(label < 0 || label==0)
    {
        return INVALID_INPUT;
    }
    /// checking if this imageID exist in this tree, if *not* we will return failure
    if(image_tree->findNode(image_tree->getRoot(),imageID)==nullptr)
    {
        return FAILURE;
    }
    /// we will save ptr for this image node
    avlRankedNode* image_ptr =  image_tree->findNode(image_tree->getRoot(),imageID);
    /// if this picture is tagged already then we will return failure
    if ( image_ptr->data_->label_array[segmentID]->element->label!=-1)
    {
       // delete image_ptr;
        //printf("here1111111111111");
        return FAILURE;
    }
    /// first, we will remove this segment from the unlabeled list
    image_ptr->data_->unlabeled_list->removeNode(image_ptr->data_->label_array[segmentID]);
    /// now we will add a new node to the labeled list of this segment
    Image_data* data= new Image_data(imageID,segmentID,label);
    image_ptr->data_->labeled_list->insertLast(imageID,data);
    /// and point to a new list node
    image_ptr->data_->label_array[segmentID]=image_ptr->data_->labeled_list->getTail();
    ///******** delete??? *********

    //delete image_ptr;
    //printf("asdalsdjljkl");
    return SUCCESS;
}

StatusType ImageTagger::GetLabel(int imageID, int segmentID, int* label)
{
    if(segmentID >segment || segmentID == segment || segmentID<0)
    {
        return INVALID_INPUT;
    }
    if(imageID<0 || imageID==0)
    {
        return INVALID_INPUT;
    }
    if(label== nullptr)
    {
        return INVALID_INPUT;
    }
    /// checking if this imageID exist in this tree, if *not* we will return failure
    if(image_tree->findNode(image_tree->getRoot(),imageID)==nullptr)
    {
        return FAILURE;
    }
    /// we will save ptr for this image node
    avlRankedNode* image_ptr =  image_tree->findNode(image_tree->getRoot(),imageID);
    ///now we will check if this segment is labeled
    if(image_ptr->data_->label_array[segmentID]->element->label ==-1 )
    {
        return FAILURE;
    }
    /// if it is labeled so we will save the label in the label variable
    *label= image_ptr->data_->label_array[segmentID]->element->label;
  //  delete image_ptr; ///******** delete??? **********
    return SUCCESS;

}

StatusType ImageTagger::DeleteLabel(int imageID, int segmentID)
{
    if(segmentID >segment || segmentID == segment || segmentID<0)
    {
        return INVALID_INPUT;
    }
    if(imageID<0 || imageID==0)
    {
        return INVALID_INPUT;
    }
    /// checking if this imageID exist in this tree, if *not* we will return failure
    if(image_tree->findNode(image_tree->getRoot(),imageID)==nullptr)
    {
        return FAILURE;
    }
    /// we will save ptr for this image node
    avlRankedNode* image_ptr =  image_tree->findNode(image_tree->getRoot(),imageID);
    /// checking if this segment is labeled
    if(image_ptr->data_->label_array[segmentID]->element->label==-1)
    {
        return FAILURE;
    }
    /// we will remove this segment from the labeled list
    image_ptr->data_->labeled_list->removeNode(image_ptr->data_->label_array[segmentID]);
    /// we will add this segment to the unlabeled list
    Image_data* data = new Image_data(imageID,segmentID,-1);
    image_ptr->data_->unlabeled_list->insertLast(imageID,data);
    // we will update the array in the segment place
  //  delete image_ptr->data_->label_array[segmentID];///******** delete??? **********
    image_ptr->data_->label_array[segmentID]= image_ptr->data_->unlabeled_list->getTail();
   // delete image_ptr;///******** delete??? **********
    return SUCCESS;
}


StatusType ImageTagger::GetAllUnlabeledSegments(int imageID, int** segments, int* numOfSegments )
{
    if( imageID < 0 || imageID == 0)
    {
        return INVALID_INPUT;
    }
    if(segments==NULL || numOfSegments ==NULL)
    {
        return INVALID_INPUT;
    }
    /// checking if this imageID exist in this tree, if *not* we will return failure
    if(image_tree->findNode(image_tree->getRoot(),imageID)==nullptr)
    {
        return FAILURE;
    }
    /// we will save ptr for this image node
    avlRankedNode* image_ptr =  image_tree->findNode(image_tree->getRoot(),imageID);
    /// we will check if there is any unlabeled area in this image
    if(image_ptr->data_->unlabeled_list->isEmpty())
    {
        return FAILURE;
    }
    /// we will save in numOfSegments variant the unlabeled amount
    *numOfSegments=image_ptr->data_->unlabeled_list->getSize();
    ///we will create a new array

   // int* segments_array = new int[*numOfSegments];
    int* segments_array = (int*)malloc((sizeof (int)) * *numOfSegments);
    /// we will enter all of the unlabeled segments of this photo to the array
    listNode* ptr= image_ptr->data_->unlabeled_list->getHead()->next;
    for (int i=0;ptr!=NULL;i++)
    {
        segments_array[i]=ptr->element->segment_number;
        ptr=ptr->next;
    }
    *segments=segments_array;
    return SUCCESS;
}


void ImageTagger::inorder_count(avlRankedNode* p ,  int& counter, int label)
{
    if(p==NULL) return ;
    inorder_count(p->left_,counter,label);
    for(int i=0;i<segment;i++)
    {
        if( p->data_->label_array[i]->element->label==label)
        {
            counter++;
        }
    }
    inorder_count(p->right_,counter,label);
}


void ImageTagger::inorder_update(avlRankedNode *p,int& index, int label, int*&images, int*&segments)
{
    if(p==NULL) return ;
    inorder_update(p->left_,index,label,images,segments);
    /// we will go over the label array of this picture and check if one of this segments is with this label
    for(int i=0;i<segment;i++)
    {
        if(p->data_->label_array[i]->element->label==label)
        {
            /// if it is, we will update the images and segment array and precede our index
            images[index]=p->data_->label_array[i]->element->imageID;
            segments[index]=p->data_->label_array[i]->element->segment_number;
            index++;
        }
    }
    inorder_update(p->right_,index,label,images,segments);
}


StatusType ImageTagger::GetAllSegmentsByLabel(int label, int** images, int**segments, int* numOfSegments)
{
    if( images ==NULL || segments ==NULL || numOfSegments==NULL)
    {
        return INVALID_INPUT;
    }
    if(label <0 || label==0)
    {
        return INVALID_INPUT;
    }
    int counter=0;
    /// we will count how much segments we have with this label
    inorder_count(image_tree->getRoot(),counter,label);
    /// now we will update the variant numOfSegments
    *numOfSegments=counter;
    /// we will create arrays that will hold the required data
    //int* segments_array = new int[counter];
    int* segments_array= (int*)malloc(sizeof (int)* counter);
    //int* images_array = new int[counter];
    int* images_array = (int*)malloc((sizeof (int)) * counter);
    int index=0;
    inorder_update(image_tree->getRoot(),index,label,images_array,segments_array);
    *segments=segments_array;
    *images=images_array;
    return SUCCESS;
}
