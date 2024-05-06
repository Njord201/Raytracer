/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PrimitivesContainer
*/

#include "Primitives/PrimitivesContainer.hpp"
#include "RaytracerRules.hpp"

#include <cmath>
#include <iostream>

void Primitive::PrimitivesContainer::add(std::shared_ptr<Primitive::IPrimitive> primitive)
{
    _primitives.push_back(primitive);
}

void Primitive::PrimitivesContainer::clear()
{
    _primitives.clear();
}

Math::Point3D Primitive::PrimitivesContainer::hitPoint(const Raytracer::Ray& ray, const Light::LightsContainer& lights) const
{
    Math::Point3D point_nearest;
    int idx_nearest = -1;

    for (size_t i = 0; i < _primitives.size(); i++) {
        Math::Point3D hit = _primitives[i]->hitPoint(ray);
        if (idx_nearest == -1 && hit.x() != -1 && hit.y() != -1 && hit.z() != -1) {
            point_nearest = _primitives[i]->hitPoint(ray);
            idx_nearest = i;
        }
        else {
            if (idx_nearest != -1 && hit.x() != -1 && hit.y() != -1 && hit.z() != -1) {
                if (hit.length() < point_nearest.length()) {
                    point_nearest = hit;
                    idx_nearest = i;
                }
            }
        }
    }
    if (idx_nearest == -1)
        return VOID_COLOR;
    //TODO : compute the color of the point based on the Material
    return _primitives[idx_nearest]->computeColor(point_nearest, lights);
}

std::vector<std::shared_ptr<Primitive::IPrimitive>> Primitive::PrimitivesContainer::getPrimitivesList(void) const
{
    return this->_primitives;
}
