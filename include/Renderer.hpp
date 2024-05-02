/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Renderer
*/

#pragma once

#include "Parser/Scene.hpp"

#include <vector>
#include <memory>

namespace Raytracer
{
   class Renderer;
};

class Raytracer::Renderer {

    public:

        /**
         * @brief Construct a new Renderer object
         *
         * @param scene to render
         */
        Renderer(Raytracer::Scene scene);

        /**
         * @brief Destroy the Renderer object
         *
         */
        ~Renderer() = default;

        /**
         * @brief render the scene
         *
         */
        void renderScene();

        /**
         * @brief write a rgb color in a stream
         * 
         * @param o stream to write in
         * @param color color to write
         */
        void writeColor(std::ostream& o, const Math::Point3D& color);

    private:

    Raytracer::Camera                   _camera;
    Primitive::PrimitivesContainer      _primitives;
    Light::LightsContainer              _lights;
};