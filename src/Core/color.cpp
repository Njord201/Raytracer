/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color
*/

#include "color.hpp"

void writeColor(std::ostream& o, const Color& color)
{
    int r = int(255.999 * color.x());
    int g = int(255.999 * color.y());
    int b = int(255.999 * color.z());

    o << r << ' ' << g << ' ' << b << '\n';
}
