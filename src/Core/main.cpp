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

    Raytracer::Scene test("tests/subject.cfg");
    return 0;
}
