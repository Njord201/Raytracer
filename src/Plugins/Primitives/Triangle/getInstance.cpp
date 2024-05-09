/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Triangle
*/

#include <iostream>

#include "Triangle.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Triangle Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getTriangleInstance()
    {
        Primitive::IPrimitive *triangle = new Primitive::Triangle();
        std::cout << "New triangle created ..." << std::endl;
        return triangle;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Triangle Plugin ..." << std::endl;
    }
}
