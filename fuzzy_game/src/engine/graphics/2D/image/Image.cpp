/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Image
*/

#include "Image.hpp"

namespace Fuzzy {

    namespace Engine {

        Image::Image(std::string filename)
        {
            _img = LoadImage(filename.c_str());
        }

        Image::Image(const Image &image)
        {
            _img = ImageCopy(image._img);
        }

        Image::~Image()
        {
            UnloadImage(_img);
        }

        void Image::resize(int newWidth, int newHeight)
        {
            ImageResize(&_img, newWidth, newHeight);
        }
    }
}