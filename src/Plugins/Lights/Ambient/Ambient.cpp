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

Light::Ambient::~Ambient()
{
}

double Light::Ambient::getMultiplier(void)
{
    return this->_multiplier;
}

void Light::Ambient::setMultiplier(double multiplier)
{
    this->_multiplier = multiplier;
}

double Light::Ambient::getDiffuseMultiplier(void)
{
    return this->_diffuseMultiplier;
}

void Light::Ambient::setDiffuseMultiplier(double diffuseMultiplier)
{
    this->_diffuseMultiplier = diffuseMultiplier;
}

Light::LightType Light::Ambient::getType(void)
{
    return Light::LightType::ambient;
}

