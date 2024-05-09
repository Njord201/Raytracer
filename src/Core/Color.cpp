/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color
*/

#include "Color.hpp"

Color::Color(double r, double g, double b) : _r(r), _g(g), _b(b)
{
}

Color::Color(Math::Point3D color)
{
    _r = color.x();
    _g = color.y();
    _b = color.z();
}

void Color::setR(double r)
{
    _r = r;
}

double Color::getR() const
{
    return _r;
}

void Color::setG(double g)
{
    _g = g;
}

double Color::getG() const
{
    return _g;
}

void Color::setB(double b)
{
    _b = b;
}

double Color::getB() const
{
    return _b;
}

bool Color::isWrongColor() const
{
    if (_r < 0 || _r > 255)
        return true;
    if (_g < 0 || _g > 255)
        return true;
    if (_b < 0 || _b > 255)
        return true;
    return false;
}
