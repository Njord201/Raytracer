/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Shadow
*/

#include "Primitives/Shadow.hpp"

#include <math.h>
#include <iostream>

Primitives::Shadow::Shadow(const std::vector<std::shared_ptr<Primitive::IPrimitive>>& primitives) : _primitives(primitives) {};

static double myRound(double value, double precision)
{
    return std::round(value / precision) * precision;
}

bool Primitives::Shadow::isShadow(const Math::Vector3D& vectorLightToPoint, const Math::Point3D& hitPoint) const
{
    Raytracer::Ray ray(hitPoint, vectorLightToPoint);
    Math::Point3D light = (Math::Point3D)hitPoint + vectorLightToPoint;

    for (size_t i = 0; i < _primitives.size(); i++) {
        Math::Point3D hit = _primitives[i]->hitPoint(ray);
        if (hit.x() != -1 && hit.y() != -1 && hit.z() != -1) {
            if ((hit.x() < hitPoint.x() && hitPoint.x() < light.x()) ||
                (hit.y() < hitPoint.y() && hitPoint.y() < light.y()) ||
                (hit.z() < hitPoint.z() && hitPoint.z() < light.z()) ||
                (hit.x() > hitPoint.x() && hitPoint.x() > light.x()) ||
                (hit.y() > hitPoint.y() && hitPoint.y() > light.y()) ||
                (hit.z() > hitPoint.z() && hitPoint.z() > light.z()))
                continue;
            if (myRound(hit.x(), 0.001) == myRound(hitPoint.x(), 0.001) &&
                myRound(hit.y(), 0.001) == myRound(hitPoint.y(), 0.001) &&
                myRound(hit.z(), 0.001) == myRound(hitPoint.z(), 0.001))
                continue;
            Math::Vector3D lightToHit = light - hit;
            if (IS_INVERSE(vectorLightToPoint.x(), lightToHit.x()) ||
                IS_INVERSE(vectorLightToPoint.y(), lightToHit.y()) ||
                IS_INVERSE(vectorLightToPoint.z(), lightToHit.z()))
                continue;
            return true;
        }
    }
    return false;
}
