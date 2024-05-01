/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Dircetional
*/

#include "Lights/Directional.hpp"


Light::Directional::Directional()
{
    this->_position = Math::Point3D(0, 0, 0);
    this->_direction = Math::Vector3D(0, 0, 0);
    this->_diffuseMultiplier = 0.0;
}

Light::Directional::Directional(Math::Point3D position, Math::Vector3D direction, double diffuseMultiplier)
{
    this->_position = position;
    this->_direction = direction;
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::Directional::~Directional()
{
}

Math::Point3D Light::Directional::getPosition(void)
{
    return this->_position;
}

void Light::Directional::setPosition(Math::Point3D position)
{
    this->_position = position;
}

Math::Vector3D Light::Directional::getDirection(void)
{
    return this->_direction;
}

void Light::Directional::setDirection(Math::Vector3D direction)
{
    this->_direction = direction;
}

double Light::Directional::getDiffuseMultiplier(void)
{
    return this->_diffuseMultiplier;
}

void Light::Directional::setDiffuseMultiplier(double diffuseMultiplier)
{
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::LightType Light::Directional::getType(void)
{
    return Light::LightType::directionnal;
}

