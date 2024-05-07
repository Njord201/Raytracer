/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color
*/

#include "Color.hpp"

Color::Color(int r, int g, int b) : _r(r), _g(g), _b(b)
{
}

void Color::setR(int r)
{
    _r = r;
}

int Color::getR() const
{
    return _r;
}

void Color::setG(int g)
{
    _g = g;
}

int Color::getG() const
{
    return _g;
}

void Color::setB(int b)
{
    _b = b;
}

int Color::getB() const
{
    return _b;
}
