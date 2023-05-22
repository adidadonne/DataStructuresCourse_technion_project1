# DataStructuresCourse_technion_project1
This is a Tehcnion data Structures course home work project number one. please read the README file for elaborated description

the project "question" / requirements :
StaticEye is a company that develops Autonomy cars.
The company wants to develop an authentication system
Able to receive an image, divides it into regions,
and tags each area with the type of object that appears in it.
Technologies of this type are usually established
Learning, meaning the system learns from images which
Tagged by a person.
The company wants your help in creating a database of
Tagged photos. You are required to build a system
which will save the IDs of all images. The system is required to support the labeling of a fixed number of regions in the image,
When the regions are numbered from 0- to segments which
is the maximum number of tags in the image.

A data structure is required to implement the following operations:

void * Init(int segments)
Time complexity: O(1)

Return value:ptr to data structore or NULL in case of a failure


StatusType AddImage(void *DS, int imageID)

Time complexity:O(log(k)+n) in the worst case, when k is the number of the photoes in the system and
n is the number of the segments in the picture


StatusType DeleteImage(void *DS, int imageID)

Time complexity:O(log(k)+n) in the worst case, when k is the number of the photoes in the system and
n is the number of the segments in the picture


StatusType AddLabel(void *DS, int imageID, int segmentID, int label)

Time complexity:O(log(k)+n) in the worst case, when k is the number of the photoes in the system and
n is the number of the segments in the picture


StatusType GetLabel(void *DS, int imageID, int segmentID, int *labl)

Time complexity:O(log(k)) in the worst case, when k is the number of the photoes in the system.


StatusType DeleteLabel(void *DS, int imageID, int segmentID)

Time complexity:O(log(k)) in the worst case, when k is the number of the photoes in the system.


StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments,
int* numOfSegments)

Time complexity:O(log(k)+s) in the worst case, when k is the number of the photoes in the system and
n is the number of the not-tag segments in the picture


StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int
*numOfSegments)

Time complexity: O(k * n) in the worst case, when k is the number of the photoes in the system and
n is the number of the segments in the picture


void Quit(void **DS)

Time complexity: O(k * n) in the worst case, when k is the number of the photoes in the system and
n is the number of the segments in the picture

space complexity:O(k * n) in the worst case, when k is the number of the photoes in the system and
n is the number of the segments in the picture



solution sort explenation:
The segments will be saved in a variable in the structure. And we will create a binary search tree whose keys will be the imageID. At each node in the tree we will save the imageID, an array of segment size, and two linked lists, one for all the untagged areas and the other for the tagged areas. The lists are lists of image_data, a variable that stores the image ID, the segment and the labeling of the image in the aforementioned segment.

picture to describe the general idea:
![image](https://github.com/adidadonne/DataStructuresCourse_technion_project1/assets/105421424/8b03cf1b-3fcf-4237-8d53-03b0d1d103ef)

the avl and list files are the implementation of those data structure, the image data files are the solution implementation 
for this project, and library2 file is the main file as requested.

אין
