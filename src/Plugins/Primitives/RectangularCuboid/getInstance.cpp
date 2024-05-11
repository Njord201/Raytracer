/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Rectangular_cuboid
*/

#include <iostream>

#include "RectangularCuboid.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Rectangular Cuboid Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getRectangularCuboidInstance()
    {
        Primitive::IPrimitive *rectangularCuboid = new Primitive::RectangularCuboid();
        std::cout << "New Rectangular Cuboid created ..." << std::endl;
        return rectangularCuboid;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Rectangular Cuboid Plugin ..." << std::endl;
    }
}
