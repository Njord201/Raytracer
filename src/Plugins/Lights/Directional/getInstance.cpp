/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Point
*/

#include <iostream>

#include "Lights/Directional.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Ambient Plugin ..." << std::endl;
    }

    Light::Directional *getDirectionalInstance()
    {
        Light::Directional *directional = new Light::Directional();
        std::cout << "New light ambient created ..." << std::endl;
        return directional;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Ambient Plugin ..." << std::endl;
    }
}
