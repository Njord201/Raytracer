/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ambient
*/

#include <iostream>

#include "Lights/Ambient.hpp"

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Ambient Plugin ..." << std::endl;
    }

    Light::Ambient *getAmbientInstance()
    {
        Light::Ambient *ambient = new Light::Ambient();
        std::cout << "New light ambient created ..." << std::endl;
        return ambient;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Ambient Plugin ..." << std::endl;
    }
}
