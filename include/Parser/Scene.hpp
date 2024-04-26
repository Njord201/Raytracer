/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <libconfig.h++>

#include "Camera/Camera.hpp"
#include "Parser/Factory.hpp"

namespace Raytracer
{
   class Scene;
};

class Raytracer::Scene {

    public:

        using PrimitivesCreator = std::function<std::unique_ptr<Primitive::IPrimitive>()>;

        /**
         * @brief Construct a new Scene object
         *
         */
        Scene(std::string filePath);

        /**
         * @brief Destruct a Scene object
         *
         */
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

        /// @brief Parse the Camera settings
        /// @param camera Settings
        /// @return 0 if no error else 84
        int _parseCameraSetting(const libconfig::Setting &camera);

        /// @brief Parse the Primitives settings
        /// @param camera Settings
        /// @return 0 if no error else 84
        int _parsePrimitiveSetting(const libconfig::Setting &primitives);

        /// @brief Parse the value of settings
        /// @param value to parse
        /// @return The value parsed
        double _parseValue(const libconfig::Setting &value);

        Camera _camera;
};
