/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <libconfig.h++>

namespace Raytracer
{
   class Scene;
};

class Raytracer::Scene {

    public:

        // Ctor
        Scene(std::string filePath);

        // Dtor
        ~Scene();
    
    private:

};
