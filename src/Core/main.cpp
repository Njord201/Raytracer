/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Core main
*/

#include <iostream>
#include "Parser/Scene.hpp"

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    std::cout << "Welcome in the Raytracer!" << std::endl << std::endl;
    try {
        Raytracer::Scene scene("tests/subject.cfg");
    } catch (const Raytracer::Scene::ParserException &parseError) {
        std::cerr << parseError.what() << std::endl;
        return 84;
    }
    return 0;
}
