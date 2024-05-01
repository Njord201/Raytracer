/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ambient
*/

#pragma once

#include <memory>

#include "ILight.hpp"

namespace Light {
    class Ambient;
};

class Light::Ambient : public Light::ILight {

    public:

        /**
         * @brief Construct a new Ambient object
         *
         */
        Ambient();

        /**
         * @brief Construct a new Ambient object
         * 
         * @param multiplier Multipler of ambient light
         * @param diffuseMultiplier Diffuse Multipler of ambient light
         */
        Ambient(double multiplier, double diffuseMultiplier);

        /**
         * @brief Destroy the Ambient object
         *
         */
        ~Ambient() = default;

        /**
         * @brief Get the Multiplier number of ambient light
         * 
         * @return double 
         */
        double getMultiplier(void) const;

        /**
         * @brief Set the Multiplier object
         * 
         * @param multiplier Multipler of ambient light to set
         */
        void setMultiplier(double multiplier);

        /**
         * @brief Get the Diffuse Multiplier number of ambient light
         * 
         * @return double 
         */
        double getDiffuseMultiplier(void) const;

        /**
         * @brief Set the Diffuse Multiplier object
         * 
         * @param diffuseMultiplier New diffuse multiplier to set
         */
        void setDiffuseMultiplier(double diffuseMultiplier);

        /**
         * @brief Get type of Light
         * @return The type of the light
         */
        Light::LightType getType(void) const override;

    private:
        double _multiplier;
        double _diffuseMultiplier;
};
