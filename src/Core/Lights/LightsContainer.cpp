/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightsContainer
*/

#include "Lights/LightsContainer.hpp"

void Light::LightsContainer::add(std::shared_ptr<Light::ILight> primitive)
{
    _Lights.push_back(primitive);
}

Light::LightsContainer::~LightsContainer()
{
}

void Light::LightsContainer::clear()
{
    _Lights.clear();
}

std::vector<std::shared_ptr<Light::ILight>> Light::LightsContainer::getLightsList(void)
{
    return this->_Lights;
}
