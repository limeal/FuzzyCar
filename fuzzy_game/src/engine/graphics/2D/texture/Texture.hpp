/*
** KOREA UNIVERSITY PROJECT, 2022
** system
** File description:
** Texture
*/

#pragma once

extern "C" {
    #include <raylib.h>
}

#include <string>

#include "../../../IRElement.hpp"
#include "../image/Image.hpp"
#include "../../color/Color.hpp"
#include "../../../maths/Vector.hpp"
#include "../../../maths/Rectangle.hpp"

namespace Fuzzy {

    namespace Engine {

        typedef enum
        {
            REPEAT = 0,    // Repeats texture in tiled mode
            CLAMP,         // Clamps texture to edge pixel in tiled mode
            MIRROR_REPEAT, // Mirrors and repeats the texture in tiled mode
            MIRROR_CLAMP   // Mirrors and clamps to border the texture in tiled mode
        } TextureWrap;

        class Texture : public IRElement<::Texture> {
            public:
                Texture() {};
                Texture(std::string fileName);
                Texture(Image image);
                Texture(Image image, int layout);
                Texture(const Texture &texture);
                ~Texture();

                void load(std::string filename);
                void setWrappingMode(int wrapMode);
                int getWidth() const {
                    if (!_isLoaded) return 0;
                    return _texture.width;
                };
                int getHeight() const {
                    if (!_isLoaded) return 0;
                    return _texture.height;
                };
                void draw(int posX, int posY, Color tint);
                void draw(Vector2d position, Color tint);
                void draw(Vector2d position, Rectangle rect, Color tint);
                void draw(Vector2d position, float rotation, float scale, Color tint);

                void unload();
                
                ::Texture getSource() { return _texture; };

                protected:
                private:
                    bool _isLoaded = false;
                    ::Texture _texture;
        };


        class RenderTexture {
            public:
                RenderTexture(int width, int height);
                ~RenderTexture();

            protected:
            private:
                ::RenderTexture _renderTexture;
        };

    }
}