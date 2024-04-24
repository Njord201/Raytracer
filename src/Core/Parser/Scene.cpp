/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#include "Parser/Scene.hpp"

Raytracer::Scene::Scene(std::string filePath)
{
    try {
        libconfig::Config cfg;

        std::cout << "filePath: [" << filePath << "]" << std::endl;
        cfg.readFile(filePath);

        const libconfig::Setting &camera = cfg.lookup("camera");
        int width = camera["resolution"]["width"];
        int height = camera["resolution"]["height"];

        double camera_x = camera["position"]["x"];
        double camera_y = camera["position"]["y"];
        double camera_z = camera["position"]["z"];

        double fov = 0.0;

        std::cout << "BEFORE" << std::endl;
        if (camera.exists("fieldOfView")) {
            double fov = camera["fieldOfView"];
        } else {
            std::cerr << "Champ 'fieldOfView' manquant dans la configuration de la caméra." << std::endl;
        }
        std::cout << "AFTER" << std::endl;






        std::cout << "width: " << "[" << width << "]" << std::endl;
        std::cout << "height: " << "[" << height << "]" << std::endl;
        std::cout << "fov: " << "[" << fov << "]" << std::endl;

        std::cout << "camera_x: " << "[" << camera_x << "]" << std::endl;
        std::cout << "camera_y: " << "[" << camera_y << "]" << std::endl;
        std::cout << "camera_z: " << "[" << camera_z << "]" << std::endl;






    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "Erreur de lecture du fichier de configuration." << std::endl;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Erreur de parsing du fichier de configuration. Ligne: " << pex.getLine() << " - " << pex.getError() << std::endl;
    }
}

Raytracer::Scene::~Scene()
{
}
