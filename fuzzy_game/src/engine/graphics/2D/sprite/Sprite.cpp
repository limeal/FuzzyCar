/*
** KOREA UNIVERSITY PROJECT, 2023
** FuzzyCar
** File description:
** Sprite
*/

#include "Sprite.hpp"
#include <iostream>

namespace Fuzzy
{
    namespace Engine
    {
        Sprite::Sprite(Texture text, int cols, int rows)
        {
            _isLoaded = true;
            _texture = text;
            _rect = Rectangle(0, 0, (float)_texture.getWidth() / cols, (float)_texture.getHeight() / rows);
        }

        Sprite::Sprite(std::string text, int cols, int rows)
        {
            _isLoaded = true;
            _texture = Texture(text);
            _rect = Rectangle(0, 0, (float)_texture.getWidth() / cols, (float)_texture.getHeight() / rows);
        }

        void Sprite::load(Texture text, int cols, int rows)
        {
            _isLoaded = true;
            _texture = text;
            _rect = Rectangle(0, 0, (float)_texture.getWidth() / cols, (float)_texture.getHeight() / rows);
        }

        void Sprite::load(std::string text, int cols, int rows)
        {
            _isLoaded = true;
            _texture.load(text);
            _rect = Rectangle(0, 0, (float)_texture.getWidth() / cols, (float)_texture.getHeight() / rows);
        }

        void Sprite::draw(Vector2d pos, Color color)
        {
            if (!_isLoaded) return;
            _rect = Rectangle(_rect.x, _rect.y, _rect.width, _rect.height);
            _texture.draw(pos, _rect, color);
        }

        void Sprite::draw(Vector2d pos, int row, int col, Color color)
        {
            if (!_isLoaded) return;
            _rect = Rectangle(_rect.width * col, _rect.height * row, _rect.width, _rect.height);
            _texture.draw(pos, _rect, color);
        }

        void Sprite::drawLeft(Vector2d pos, Color color)
        {
            if (!_isLoaded) return;
            if (_rect.width + _rect.x >= _texture.getWidth())
                _rect = Rectangle(0, _rect.y, _rect.width, _rect.height);
            else
                _rect = Rectangle(_rect.x + _rect.width, _rect.y, _rect.width, _rect.height);
            _texture.draw(pos, _rect, color);
        }

        void Sprite::drawDown(Vector2d pos, Color color)
        {
            if (!_isLoaded) return;
            if (_rect.height + _rect.y >= _texture.getHeight())
                _rect = Rectangle(_rect.x, 0, _rect.width, _rect.height);
            else
                _rect = Rectangle(_rect.x, _rect.y + _rect.height, _rect.width, _rect.height);
            _texture.draw(pos, _rect, color);
        }

        void Sprite::unload()
        {
            if (!_isLoaded) return;
            _isLoaded = false;
            _texture.unload();
        }
    }
}