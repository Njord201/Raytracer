/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include <iostream>

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Sphere Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getInstance()
    {
        return new Primitive::Sphere();
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Sphere Plugin ..." << std::endl;
    }
}
