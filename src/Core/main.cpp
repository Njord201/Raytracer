/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Core main
*/

#include <iostream>

#include "Parser/Scene.hpp"
#include "Renderer.hpp"

bool displayHelp(int argc, char **argv)
{
    if ((argc == 2) && (argv[1] == std::string("--help"))) {
        std::cout << "USAGE: ./raytracer <SCENE_FILE>" << std::endl;
        std::cout << "\tSCENE_FILE: scene configuration" << std::endl;
        return true;
    }
    return false;
}

int main(int argc, char **argv)
{
    if (displayHelp(argc, argv))
        return 0;
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
