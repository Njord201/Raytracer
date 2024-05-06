/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Point
*/

#include <iostream>

#include "Lights/Point.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Ambient Plugin ..." << std::endl;
    }

    Light::Point *getPointInstance()
    {
        Light::Point *point = new Light::Point();
        std::cout << "New light ambient created ..." << std::endl;
        return point;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Ambient Plugin ..." << std::endl;
    }
}
