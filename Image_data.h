
#ifndef WET1SUMMER_IMAGE_DATA_H

class Image_data{
    friend class ImageTagger;
    friend class ImageTreeData;
private:
    int imageID;
    int segment_number;
    int label;

public:
    //Image_data(): imageID
    Image_data(int imageID, int segment_number, int label): imageID(imageID), segment_number(segment_number) , label(label){}
    Image_data(Image_data& i)=default;
    Image_data& operator=(Image_data& i)=default;
    ~Image_data()=default;

};


#endif //WET1SUMMER_IMAGE_DATA_H
