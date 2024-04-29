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

Primitive::PrimitivesContainer::~PrimitivesContainer()
{
}

void Primitive::PrimitivesContainer::clear()
{
    _primitives.clear();
}

Math::Point3D Primitive::PrimitivesContainer::hitPoint(const Raytracer::Ray& ray) const
{
    for (size_t i = 0; i < _primitives.size(); i++) {
        _primitives[i]->hitPoint(ray);
        // TODO : implement the hitpoint logic
    }
    Math::Point3D temp(0, 0, 0);
    return temp;
}

std::vector<std::shared_ptr<Primitive::IPrimitive>> Primitive::PrimitivesContainer::getPrimitivesList(void)
{
    return this->_primitives;
}
