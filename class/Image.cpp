#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"


Image::Image(const char *filename){ // ! Constructor
    if (read(filename)){
        cout << "Read: " << filename << std::endl;
        size = w * h * channels;
    }
    else {
        cout << "Failed to read: " << filename << std::endl;
    };
};

Image::~Image(){ // ! Destructor
    stbi_image_free(data);
};

bool Image::read(const char *filename){ // ! Reads image
    data = stbi_load(filename, &w, &h, &channels, 0);
    return data != NULL;
};

bool Image::write(const char *filename, uint8_t *newData){ // ! Writes image
    stbi_write_png(filename, this->w, this->h, this->channels, newData, this->w * this->channels);
    return data != NULL;
};

