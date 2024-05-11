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

Math::Point3D Primitive::Mesh::hitPoint(const Raytracer::Ray& ray)
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
        return Math::Vector3D(-1, -1, -1);
    _lastHit = _primitives[idx_nearest];
    return point_nearest;
}

Math::Vector3D Primitive::Mesh::getNormal(const Math::Vector3D& hitPoint, const Raytracer::Ray& ray) const
{
    return _lastHit->getNormal(hitPoint, ray);
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

void Primitive::Mesh::add(std::shared_ptr<Primitive::IPrimitive> primitive)
{
    _primitives.push_back(primitive);
}
