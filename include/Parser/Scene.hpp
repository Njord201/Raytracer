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

#include "Camera/Camera.hpp"

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

        class ParserException : public std::exception {
            public:
                /// @brief Exception to throw when there is an error in parsing
                /// @param msg message to throw
                explicit ParserException(const std::string &msg) : message(msg) {}
                
                /// @brief Return the message of error
                /// @return message
                virtual const char* what() const noexcept override {
                    return message.c_str();
                }

            private:
                std::string message;
        };
    
    private:

        int _parseCameraSetting(const libconfig::Setting &camera);

        double _parseValue(const libconfig::Setting &value);

        Camera _camera;
};
