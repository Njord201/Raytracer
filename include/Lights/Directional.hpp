/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Directional
*/

#pragma once

#include <memory>

#include "ILight.hpp"
#include "Math/Vector3D.hpp"

namespace Light {
    class Directional;
};

class Light::Directional : public Light::ILight {

    public:

        /**
         * @brief Construct a new Directional object
         *
         */
        Directional();

        /**
         * @brief Construct a new Directional object
         *
         */
        Directional(Math::Point3D position, Math::Vector3D direction, double diffuseMultiplier);

        /**
         * @brief Destroy the Directional object
         *
         */
        ~Directional();

        /**
         * @brief Get the Position number of Point light
         * 
         * @return double 
         */
        Math::Point3D getPosition(void);

        /**
         * @brief Set the Position number of Point light
         */
        void setPosition(Math::Point3D position);

        /**
         * @brief Get the Direction number of Point light
         * 
         * @return double 
         */
        Math::Vector3D getDirection(void);

        /**
         * @brief Set the Direction number of Point light
         */
        void setDirection(Math::Vector3D direction);

        /**
         * @brief Get the Diffuse Multiplier number of Point light
         * 
         * @return double 
         */
        double getDiffuseMultiplier(void);

        /**
         * @brief Set the Diffuse Multiplier number of Point light
         */
        void setDiffuseMultiplier(double diffuseMultiplier);

        /**
         * @brief Get type of Light
         * @return The type of the light
         */
        Light::LightType getType(void) override;

    private:
        Math::Point3D    _position;
        Math::Vector3D   _direction;
        double           _diffuseMultiplier;
};
