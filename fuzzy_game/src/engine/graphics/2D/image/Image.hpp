/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Image
*/

#pragma once

extern "C" {
    #include <raylib.h>
}

#include <string>

#include "../../../IRElement.hpp"

namespace Fuzzy {
    namespace Engine {
        class Image : public IRElement<::Image> {
            public:
                Image(std::string filename);
                Image(const Image &image);
                ~Image();

                void resize(int newWidth, int newHeight);
                ::Image getSource() { return _img; };

            protected:
            private:
                ::Image _img;
        };
    }
}