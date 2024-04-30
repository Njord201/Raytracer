/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Core main
*/

#include <iostream>

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
    std::cout << "Welcome in the Raytracer!" << std::endl;
    return 0;
}
