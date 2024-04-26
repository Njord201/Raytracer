/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include <iostream>

#include "Sphere.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Sphere Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getSphereInstance()
    {
        Primitive::IPrimitive *sphere = new Primitive::Sphere();
        std::cout << "New sphere created ..." << std::endl;
        return sphere;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Sphere Plugin ..." << std::endl;
    }
}
