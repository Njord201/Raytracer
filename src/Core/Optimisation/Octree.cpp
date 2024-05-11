/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Octree
*/

#include "Optimisation/Octree.hpp"

using Octree = Optimisation::Octree;

Octree::Octree(PrimitivesContainer primitives, cubeCollider cubeCollider)
{
    _cube = Cube(cubeCollider, primitives, 3);
}

PrimitivesContainer Octree::getPrimitivesHits(const Raytracer::Ray &ray) const
{
    return _cube.getPrimitivesHits(ray);
}
