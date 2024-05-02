/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include <iostream>

#include "Cylinder.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Cylinder Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getCylinderInstance()
    {
        Primitive::IPrimitive *cylinder = new Primitive::Cylinder();
        std::cout << "New Cylinder created ..." << std::endl;
        return cylinder;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Cylinder Plugin ..." << std::endl;
    }
}
