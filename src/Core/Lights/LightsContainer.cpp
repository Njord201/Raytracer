/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** LightsContainer
*/

#include "Lights/LightsContainer.hpp"

#include <cmath>

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

Color Light::LightsContainer::computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const
{
    Color highColor;

    for (size_t i = 0; i < _Lights.size(); i++) {
        Color colorFind = _Lights[i]->computeColor(primitiveNormal, hitPoint, color, shadow);
        if (sqrt(highColor.getR() * highColor.getR() + highColor.getG() * highColor.getG() + highColor.getB() * highColor.getB()) <
            sqrt(colorFind.getR() * colorFind.getR() + colorFind.getG() * colorFind.getG() + colorFind.getB() * colorFind.getB()))
            highColor = colorFind;
    }
    return Color(highColor);
}
