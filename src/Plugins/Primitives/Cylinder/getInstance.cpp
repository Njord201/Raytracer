/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

#include <iostream>

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Cylinder Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getInstance()
    {
        return new Primitive::Cylinder();
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Cylinder Plugin ..." << std::endl;
    }
}
