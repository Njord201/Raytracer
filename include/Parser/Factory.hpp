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

#include "Parser/DLLoader.hpp"
#include "Primitives/Sphere.hpp"

namespace Raytracer
{
   class Factory;
};

class Raytracer::Factory {

    public:

        using PrimitivesCreator = std::function<std::shared_ptr<Primitive::IPrimitive>()>;

        /**
         * @brief Construct a new Scene object
         *
         */
        Factory();

        /**
         * @brief Destruct a Scene object
         *
         */
        ~Factory();

        /// @brief Create a type component
        /// @param type Component to create
        /// @return The Component
        std::shared_ptr<Primitive::IPrimitive> createComponent(const std::string &type);

        /// @brief Register a type component 
        /// @param type Component to register
        /// @param creator Function to create the component
        void registerComponent(const std::string& type, PrimitivesCreator creator);
    
    private:
        std::unordered_map<std::string, PrimitivesCreator>   _componentPrimitivesList;
        std::vector<std::shared_ptr<DLLoader>> _libraryLoader;
};
