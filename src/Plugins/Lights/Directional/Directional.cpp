/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Dircetional
*/

#include "Lights/Directional.hpp"

#include <cmath>
#include <iostream>

Light::Directional::Directional()
{
    this->_position = Math::Point3D(0, 0, 0);
    this->_direction = Math::Vector3D(0, 0, 0);
    this->_diffuseMultiplier = 0.0;
    this->_color = Color(-1, -1, -1);
}

Light::Directional::Directional(Math::Point3D position, Math::Vector3D direction, double diffuseMultiplier)
{
    this->_position = position;
    this->_direction = direction;
    this->_diffuseMultiplier = diffuseMultiplier;
    this->_color = Color(-1, -1, -1);
}

Math::Point3D Light::Directional::getPosition(void) const
{
    return this->_position;
}

void Light::Directional::setPosition(Math::Point3D position)
{
    this->_position = position;
}

Math::Vector3D Light::Directional::getDirection(void) const
{
    return this->_direction;
}

void Light::Directional::setDirection(Math::Vector3D direction)
{
    this->_direction = direction;
}

double Light::Directional::getDiffuseMultiplier(void) const
{
    return this->_diffuseMultiplier;
}

void Light::Directional::setDiffuseMultiplier(double diffuseMultiplier)
{
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::LightType Light::Directional::getType(void) const
{
    return Light::LightType::directionnal;
}

Color Light::Directional::computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const
{
    Math::Vector3D normal = primitiveNormal / primitiveNormal.length();
    Math::Vector3D dir = getDirection() / getDirection().length();

    // TODO : rewrite method to handle the position of the
    // directional light

    if (shadow.isShadow(dir * -1, hitPoint))
        return Math::Point3D(0,0,0);

    color *= -normal.dot(dir);

    if (color.x() < 0)
        color = Math::Point3D(0, color.y(), color.z());
    if (color.y() < 0)
        color = Math::Point3D(color.x(), 0, color.z());
    if (color.z() < 0)
        color = Math::Point3D(color.x(), color.y(), 0);


    return color;
}

void Light::Directional::setColor(const Color& rgb)
{
    _color = rgb;
}

Color Light::Directional::getColor(void) const
{
    return _color;
}