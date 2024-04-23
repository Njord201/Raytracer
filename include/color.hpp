/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color
*/

#pragma once

#include "Vector3D.hpp"

#include <ostream>

using Color = Math::Vector3D;

/**
 * @brief write color in a stream
 *
 * @param o stream
 * @param color vector3D
 */
void writeColor(std::ostream& o, const Color& color);
