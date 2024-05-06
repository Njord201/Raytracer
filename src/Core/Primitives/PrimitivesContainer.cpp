/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** PrimitivesContainer
*/

#include "Primitives/PrimitivesContainer.hpp"
#include "RaytracerRules.hpp"
#include "Materials/FlatColor.hpp"
#include "Primitives/Shadow.hpp"

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

    return computeColor(_primitives[idx_nearest], point_nearest, lights);
}

Math::Point3D Primitive::PrimitivesContainer::computeColor(const std::shared_ptr<Primitive::IPrimitive>& primitive, const Math::Point3D& hitPoint, const Light::LightsContainer& lights) const
{
    Math::Vector3D normal = primitive->getNormal(hitPoint);

    if (primitive->getMaterial()->getType() == Material::MaterialType::FlatColor) {
        std::shared_ptr<FlatColor> primitiveFlatColor = std::dynamic_pointer_cast<FlatColor>(primitive->getMaterial());
        return lights.computeColor(normal, hitPoint, Math::Point3D(primitiveFlatColor->getR(), primitiveFlatColor->getG(), primitiveFlatColor->getB()), Primitives::Shadow(_primitives));
    }
    std::cout << "material not handle in sphere" << std::endl;
    return VOID_COLOR;
}

std::vector<std::shared_ptr<Primitive::IPrimitive>> Primitive::PrimitivesContainer::getPrimitivesList(void) const
{
    return this->_primitives;
}
