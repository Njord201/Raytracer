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

void Light::LightsContainer::clear()
{
    _Lights.clear();
}

std::vector<std::shared_ptr<Light::ILight>> Light::LightsContainer::getLightsList(void) const
{
    return this->_Lights;
}

Math::Point3D Light::LightsContainer::computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const
{
    Math::Point3D highColor;

    for (size_t i = 0; i < _Lights.size(); i++) {
        Math::Point3D colorFind = _Lights[i]->computeColor(primitiveNormal, hitPoint, color, shadow);
        if (highColor.length() < colorFind.length() ) {
            highColor = colorFind;
        }
    }
    return highColor;
}
