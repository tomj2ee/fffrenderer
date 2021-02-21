#include <iostream>
#include <cstring>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main()
{
    std::cout << "fffrenderer" << std::endl;

    int w = 100, h = 100, n = 3;
    unsigned long nbytes = w*h*n;
    unsigned char* data;

    data = new unsigned char[nbytes];
    std::memset(data, 0, nbytes);

    int rw = 20, rh = 20;
    unsigned char red[3] = {255, 0, 0};
    for (int i = 0; i < rw; i++)
    {
        for (int j = 0; j < rh; j++)
        {
            std::memcpy(data+(i+j*w)*n, red, n);
        }
    }

    if (stbi_write_bmp("build/output.bmp", w, h, n, data) )
    {
        std::cout << "build/output.bmp success" << std::endl;
    }

    return 0;
}