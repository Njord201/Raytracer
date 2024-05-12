/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Mesh
*/

#include <iostream>

#include "Mesh.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Mesh Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getMeshInstance()
    {
        Primitive::IPrimitive *mesh = new Primitive::Mesh();
        std::cout << "New Mesh created ..." << std::endl;
        return mesh;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Mesh Plugin ..." << std::endl;
    }
}
