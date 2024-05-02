/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Core main
*/

#include <iostream>

#include "Parser/Scene.hpp"
#include "Renderer.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
        return 84;
    try {
        Raytracer::Scene scene(argv[1]);
        Raytracer::Renderer renderer(scene);
        renderer.renderScene();
    } catch (const Raytracer::Scene::ParserException &parseError) {
        std::cerr << parseError.what() << std::endl;
        return 84;
    }
    return 0;
}
