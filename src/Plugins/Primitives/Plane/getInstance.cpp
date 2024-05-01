/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** getInstance
*/

#include "Plane.hpp"

#include <iostream>

extern "C"
{
    __attribute__((constructor))
    static void initSharedlibrary()
    {
        std::cout << "Loading Plane Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getInstance()
    {
        return new Primitive::Plane();
    }

    __attribute__((destructor))
    static void destroySharedlibrary()
    {
        std::cout << "Closing Plane Plugin ..." << std::endl;
    }
}
