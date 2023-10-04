/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Material
*/

#pragma once

extern "C" {
    #include <raylib.h>
}

#include <string>

#include "../../../IRElement.hpp"
#include "../../2D/2D.hpp"
#include "../../color/Color.hpp"

namespace Fuzzy {
    namespace Engine {
        class Material : public IRElement<::Material> {
            public:
                Material(std::string filename, int *materialCount);
                Material(const Material &mat);
                ~Material();
                
                void setTexture(int mapType, Texture texture) { SetMaterialTexture(_monMat, mapType, texture.getSource()); };

                ::Material getSource() { return *_monMat; };
            
            protected:
            private:
                ::Material *_monMat;
        };
    }
}