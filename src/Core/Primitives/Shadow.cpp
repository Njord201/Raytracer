/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Shadow
*/

#include "Primitives/Shadow.hpp"

#include <iostream>

Primitives::Shadow::Shadow(const std::vector<std::shared_ptr<Primitive::IPrimitive>>& primitives) : _primitives(primitives) {};

bool Primitives::Shadow::isShadow(const Math::Vector3D& vectorLightToPoint, const Math::Point3D& hitPoint) const
{
    Raytracer::Ray ray(hitPoint, vectorLightToPoint);
    Math::Point3D h = hitPoint;
    Math::Vector3D vltp =vectorLightToPoint;
    Math::Point3D light = h + vltp;

    for (size_t i = 0; i < _primitives.size(); i++) {
        Math::Point3D hit = _primitives[i]->hitPoint(ray);
        if (hit.x() != -1 && hit.y() != -1 && hit.z() != -1) {
            // std::cout << hit.x() << " " << hit.y() << " " << hit.z() << " -> " << hitPoint.x() << " " << hitPoint.y() << " " << hitPoint.z() << std::endl;
            if ((hit.x() < hitPoint.x() && hitPoint.x() < light.x()) ||
                (hit.y() < hitPoint.y() && hitPoint.y() < light.y()) ||
                (hit.z() < hitPoint.z() && hitPoint.z() < light.z()) ||
                (hit.x() > hitPoint.x() && hitPoint.x() > light.x()) ||
                (hit.y() > hitPoint.y() && hitPoint.y() > light.y()) ||
                (hit.z() > hitPoint.z() && hitPoint.z() > light.z()))
                continue;
            return true;
        }
    }
    return false;
}
