/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cone
*/

#include <iostream>

#include "Cone.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Cone Plugin ..." << std::endl;
    }

    Primitive::IPrimitive *getConeInstance()
    {
        Primitive::IPrimitive *cone = new Primitive::Cone();
        std::cout << "New Cone created ..." << std::endl;
        return cone;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Cone Plugin ..." << std::endl;
    }
}
