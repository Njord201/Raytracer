/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ambient
*/

#include "Lights/Ambient.hpp"

Light::Ambient::Ambient()
{
    this->_multiplier = 0.0;
    this->_diffuseMultiplier = 0.0;
}

Light::Ambient::Ambient(double multiplier, double diffuseMultiplier)
{
    this->_multiplier = multiplier;
    this->_diffuseMultiplier = diffuseMultiplier;
}

double Light::Ambient::getMultiplier(void) const
{
    return this->_multiplier;
}

void Light::Ambient::setMultiplier(double multiplier)
{
    this->_multiplier = multiplier;
}

double Light::Ambient::getDiffuseMultiplier(void) const
{
    return this->_diffuseMultiplier;
}

void Light::Ambient::setDiffuseMultiplier(double diffuseMultiplier)
{
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::LightType Light::Ambient::getType(void) const
{
    return Light::LightType::ambient;
}

Math::Point3D Light::Ambient::computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const
{
    (void) shadow;
    (void) primitiveNormal;
    (void) hitPoint;
    color *= _multiplier;
    return color;
}
