/*
** EPITECH PROJECT, 2024
** FlatColors
** File description:
** Raytracer
*/

#include "Materials/FlatColor.hpp"


FlatColor::FlatColor()
{
    this->_r = 0;
    this->_g = 0;
    this->_b = 0;
}

FlatColor::FlatColor(int r, int g, int b)
{
    this->_r = r;
    this->_g = g;
    this->_b = b;
}

FlatColor::~FlatColor()
{
}

Material::MaterialType FlatColor::getType(void)
{
    return Material::FlatColor;
}

void FlatColor::setR(int r)
{
    this->_r = r;
}

void FlatColor::setG(int g)
{
    this->_g = g;
}

void FlatColor::setB(int b)
{
    this->_b = b;
}

int FlatColor::getR(void)
{
    return this->_r;
}

int FlatColor::getG(void)
{
    return this->_g;
}

int FlatColor::getB(void)
{
    return this->_b;
}

