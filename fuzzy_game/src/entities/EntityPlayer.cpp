/*
** EPITECH PROJECT, 2023
** FuzzyCar
** File description:
** EntityPlayer
*/

#include "EntityPlayer.hpp"

Fuzzy::EntityPlayer::EntityPlayer(SDL::Sprite &sprite, SDL::Vector2i position, SDL::Vector2i direction) :
    EntityCar(sprite, position, direction)
{

}

void Fuzzy::EntityPlayer::consume(SDL::Event *event)
{

}