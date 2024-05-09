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
#include "Primitives/Cone.hpp"
#include "Primitives/Cylinder.hpp"
#include "Primitives/Plane.hpp"
#include "Lights/Point.hpp"
#include "Lights/Ambient.hpp"
#include "Lights/Directional.hpp"

namespace Raytracer
{
   class Factory;
};

class Raytracer::Factory {

    public:

        using PrimitivesCreator = std::function<std::shared_ptr<Primitive::IPrimitive>()>;
        using LightsCreator = std::function<std::shared_ptr<Light::ILight>()>;

        /**
         * @brief Construct a new Scene object
         *
         */
        Factory();

        /**
         * @brief Destruct a Scene object
         *
         */
        ~Factory() = default;

        /*
         * @brief Create a type component
         * @param type Component to create
         * @return The Component
         */
        std::shared_ptr<Primitive::IPrimitive> createPrimitivesComponent(const std::string &type);

        /*
         * @brief Register a type component
         * @param type Component to register
         * @param creator Function to create the component
         */
        void registerPrimitivesComponent(const std::string& type, PrimitivesCreator creator);

        /*
         * @brief Create a type component
         * @param type Component to create
         * @return The Component
         */
        std::shared_ptr<Light::ILight> createLightsComponent(const std::string &type);

        /*
         * @brief Register a type component
         * @param type Component to register
         * @param creator Function to create the component
         */
        void registerLightsComponent(const std::string& type, LightsCreator creator);

    private:
        std::unordered_map<std::string, PrimitivesCreator>   _componentPrimitivesList;
        std::unordered_map<std::string, LightsCreator>       _componentLightsList;
        std::vector<std::shared_ptr<DLLoader>>               _libraryLoader;
};
