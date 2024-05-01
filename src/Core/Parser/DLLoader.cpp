/*
** EPITECH PROJECT, 2024
** DLLoader
** File description:
** Raytracer
*/

#include "Parser/DLLoader.hpp"

Raytracer::DLLoader::DLLoader(const std::string libraryPath)
{
    _libraryPath = libraryPath;
    _libraryInstance = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!_libraryInstance) {
        throw std::runtime_error(dlerror());
    }
}

Raytracer::DLLoader::~DLLoader()
{
    if (dlclose(_libraryInstance) != 0) {
        std::cout << "ERROR: " << dlerror() << std::endl;
    }
}


