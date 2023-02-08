#pragma once
#include <stdint.h>
#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"
#include <iostream>

using namespace std;

struct Image {
    uint8_t *data = NULL;
    size_t size = 0;
    int w;
    int h;
    int channels;

    Image(const char* filename);
    Image(int w, int h, int channels);
    ~Image();

    bool read(const char* filename);
    bool write(const char* filename, uint8_t *newData);
};