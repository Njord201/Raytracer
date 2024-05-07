/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ambient
*/

#include "Lights/Point.hpp"
#include "RaytracerRules.hpp"

#include <cmath>

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

Math::Point3D Light::Point::getPosition(void) const
{
    return this->_position;
}

void Light::Point::setPosition(Math::Point3D position)
{
    this->_position = position;
}

double Light::Point::getDiffuseMultiplier(void) const
{
    return this->_diffuseMultiplier;
}

void Light::Point::setDiffuseMultiplier(double diffuseMultiplier)
{
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::LightType Light::Point::getType(void) const
{
    return Light::LightType::point;
}

Math::Point3D Light::Point::computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const
{
    Math::Vector3D light = _position;
    Math::Vector3D vectorLightToPoint = light - hitPoint;

    if (shadow.isShadow(vectorLightToPoint, hitPoint))
        return SHADOW_COLOR;

    double n = primitiveNormal.dot(vectorLightToPoint);
    double d  = primitiveNormal.length() * vectorLightToPoint.length();

    double angle = acos(n / d) * 180 / M_PI;

    double coeffLight = (1 - (angle / 90));

    if (angle <= 90)
        color *= coeffLight;
    else
        color = Math::Point3D(0,0,0);

    return color;
}
