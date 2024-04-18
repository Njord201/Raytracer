/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Lights
*/

#include <iostream>

extern "C"
{
    __attribute__((constructor))
    static void initsharedlibrary()
    {
        std::cout << "Loading Lights Plugin ..." << std::endl;
    }

    __attribute__((destructor))
    static void destroysharedlibrary()
    {
        std::cout << "Closing Lights Plugin ..." << std::endl;
    }
}
