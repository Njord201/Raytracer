/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PrimitivesContainer
*/

#include "Primitives/PrimitivesContainer.hpp"

void Primitive::PrimitivesContainer::add(std::shared_ptr<Primitive::IPrimitive> primitive)
{
    _primitives.push_back(primitive);
}

void Primitive::PrimitivesContainer::clear()
{
    _primitives.clear();
}

Math::Point3D Primitive::PrimitivesContainer::hitPoint(const Raytracer::Ray& ray) const
{
    Math::Point3D point_nearest;
    int idx_nearest = -1;

    for (size_t i = 0; i < _primitives.size(); i++) {
        if (i == 0) {
            point_nearest = _primitives[i]->hitPoint(ray);
            idx_nearest = i;
        }
        else {
            Math::Point3D hit = _primitives[i]->hitPoint(ray);
            if (hit.length() < point_nearest.length()) {
                point_nearest = hit;
                idx_nearest = i;
            }
        }
    }
    if (idx_nearest == -1)
        return Math::Point3D(0, 0, 0);

    Math::Point3D temp(0, 0, 0);
    //TODO : compute the color of the point based on the Material
    return temp;
}

std::vector<std::shared_ptr<Primitive::IPrimitive>> Primitive::PrimitivesContainer::getPrimitivesList(void) const
{
    return this->_primitives;
}
