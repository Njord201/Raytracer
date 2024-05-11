/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Mesh
*/

#include "Primitives/Mesh.hpp"

Primitive::Mesh::Mesh()
{

}

Math::Point3D Primitive::Mesh::hitPoint(const Raytracer::Ray& ray) const
{
    (void) ray;
    return Math::Vector3D();
}

Math::Vector3D Primitive::Mesh::getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const
{
    (void) hitPoint;
    (void) ray;
    return Math::Vector3D();
}

std::shared_ptr<Material::IMaterial> Primitive::Mesh::getMaterial() const
{
    return _material;
}

Octree::cubeCollider Primitive::Mesh::getColliderBox() const
{
    return _collider;
}

void Primitive::Mesh::setMaterial(std::shared_ptr<Material::IMaterial> material)
{
    this->_material = material;
}
