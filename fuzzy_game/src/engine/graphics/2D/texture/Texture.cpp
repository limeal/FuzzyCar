/*
** KOREA UNIVERSITY PROJECT, 2022
** system
** File description:
** Texture
*/

#include "Texture.hpp"

namespace Fuzzy
{
    namespace Engine
    {
        Texture::Texture(std::string fileName)
        {
            _isLoaded = true;
            _texture = LoadTexture(fileName.c_str());
        }

        Texture::Texture(Image image)
        {
            _isLoaded = true;
            _texture = LoadTextureFromImage(image.getSource());
        }

        Texture::Texture(const Texture &texture)
        {
            _isLoaded = true;
            _texture = texture._texture;
        }
        
        Texture::Texture(Image image, int layout)
        {
            _isLoaded = true;
            _texture = LoadTextureCubemap(image.getSource(), layout);
        }

        Texture::~Texture()
        {
            unload();
        }
        
        void Texture::load(std::string filename)
        {
            _isLoaded = true;
            _texture = LoadTexture(filename.c_str());
        }

        void Texture::setWrappingMode(int wrapMode)
        {
            if (!_isLoaded) return;
            SetTextureWrap(_texture, wrapMode);
        }

        void Texture::draw(int posX, int posY, Color tint)
        {
            if (!_isLoaded) return;
            DrawTexture(_texture, posX, posY, tint.getSource());
        }

        void Texture::draw(Vector2d position, Color tint)
        {
            if (!_isLoaded) return;
            DrawTextureV(_texture, position.getSource(), tint.getSource());
        }

        void Texture::draw(Vector2d position, float rotation, float scale, Color tint)
        {
            if (!_isLoaded) return;
            DrawTextureEx(_texture, position.getSource(), rotation, scale, tint.getSource());
        }
        
        void Texture::draw(Vector2d position, Rectangle rect, Color tint)
        {
            if (!_isLoaded) return;
            DrawTextureRec(_texture, rect.getSource(), position.getSource(), tint.getSource());
        }

        void Texture::unload()
        {
            if (!_isLoaded) return;
            _isLoaded = false;
            UnloadTexture(_texture);
        }
        RenderTexture::RenderTexture(int width, int height)
        {
            _renderTexture = LoadRenderTexture(width, height);
        }

        RenderTexture::~RenderTexture()
        {
            UnloadRenderTexture(_renderTexture);
        }

    }
}