/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ambient
*/

#include "Lights/Point.hpp"


Light::Point::Point()
{
    this->_position = Math::Point3D(0, 0, 0);
    this->_diffuseMultiplier = 0.0;
}

Light::Point::Point(Math::Point3D position, double diffuseMultiplier)
{
    this->_position = position;
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::Point::~Point()
{
}

Math::Point3D Light::Point::getPosition(void)
{
    return this->_position;
}

void Light::Point::setPosition(Math::Point3D position)
{
    this->_position = position;
}

double Light::Point::getDiffuseMultiplier(void)
{
    return this->_diffuseMultiplier;
}

void Light::Point::setDiffuseMultiplier(double diffuseMultiplier)
{
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::LightType Light::Point::getType(void)
{
    return Light::LightType::point;
}
