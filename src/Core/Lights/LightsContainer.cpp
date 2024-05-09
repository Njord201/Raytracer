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
    Color rgb;
    Color coeff(0, 0, 0);
    size_t nbHitLight = 1;

    for (size_t i = 0; i < _Lights.size(); i++) {
        Color colorFind = _Lights[i]->computeColor(primitiveNormal, hitPoint, color, shadow);
        if (colorFind.getR() == 0 && colorFind.getG() == 0 && colorFind.getB() == 0)
            continue;
        if (sqrt(rgb.getR() * rgb.getR() + rgb.getG() * rgb.getG() + rgb.getB() * rgb.getB()) <
            sqrt(colorFind.getR() * colorFind.getR() + colorFind.getG() * colorFind.getG() + colorFind.getB() * colorFind.getB()))
            rgb = colorFind;
        if (not _Lights[i]->getColor().isWrongColor()) {
            nbHitLight+=1;
            coeff = Color(coeff.getR() + _Lights[i]->getColor().getR(), coeff.getG() + _Lights[i]->getColor().getG(), coeff.getB() + _Lights[i]->getColor().getB());
        }
    }
    rgb = Color((rgb.getR() + coeff.getR()) / nbHitLight, (rgb.getG() + coeff.getG()) / nbHitLight, (rgb.getB() + coeff.getB()) / nbHitLight);

    Color highColor;
    for (size_t i = 0; i < _Lights.size(); i++) {
        Color colorFind = _Lights[i]->computeColor(primitiveNormal, hitPoint, Math::Vector3D(rgb.getR(), rgb.getG(), rgb.getB()), shadow);
        if (sqrt(highColor.getR() * highColor.getR() + highColor.getG() * highColor.getG() + highColor.getB() * highColor.getB()) <
            sqrt(colorFind.getR() * colorFind.getR() + colorFind.getG() * colorFind.getG() + colorFind.getB() * colorFind.getB()))
            highColor = colorFind;
    }
    return Color(highColor);
}
