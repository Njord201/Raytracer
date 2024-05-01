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
         */
        Ambient(double multiplier, double diffuseMultiplier);

        /**
         * @brief Destroy the Ambient object
         *
         */
        ~Ambient();

        /**
         * @brief Get the Multiplier number of ambient light
         * 
         * @return double 
         */
        double getMultiplier(void);

        /**
         * @brief Set the Multiplier number of ambient light
         */
        void setMultiplier(double multiplier);

        /**
         * @brief Get the Diffuse Multiplier number of ambient light
         * 
         * @return double 
         */
        double getDiffuseMultiplier(void);

        /**
         * @brief Set the Diffuse Multiplier number of ambient light
         */
        void setDiffuseMultiplier(double diffuseMultiplier);

        /**
         * @brief Get type of Light
         * @return The type of the light
         */
        Light::LightType getType(void) override;

    private:
        double _multiplier;
        double _diffuseMultiplier;
};
