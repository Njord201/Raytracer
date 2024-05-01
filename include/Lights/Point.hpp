/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Point
*/

#pragma once

#include <memory>

#include "ILight.hpp"
#include "Math/Vector3D.hpp"

namespace Light {
    class Point;
};

class Light::Point : public Light::ILight {

    public:

        /**
         * @brief Construct a new Point object
         *
         */
        Point();

        /**
         * @brief Construct a new Point object
         * 
         * @param position Position of Point Light
         * @param diffuseMultiplier Diffuse multiplier of Point Light
         */
        Point(Math::Point3D position, double diffuseMultiplier);

        /**
         * @brief Destroy the Point object
         *
         */
        ~Point() = default;

        /**
         * @brief Get the Position number of Point light
         * 
         * @return double 
         */
        Math::Point3D getPosition(void) const;

        /**
         * @brief Set the Position object
         * 
         * @param position New position of Point Light
         */
        void setPosition(Math::Point3D position);

        /**
         * @brief Get the Diffuse Multiplier number of Point light
         * 
         * @return double 
         */
        double getDiffuseMultiplier(void) const;

        /**
         * @brief Set the Diffuse Multiplier object
         * 
         * @param diffuseMultiplier New Diffuse Multiplier of Point Light
         */
        void setDiffuseMultiplier(double diffuseMultiplier);

        /**
         * @brief Get type of Light
         * @return The type of the light
         */
        Light::LightType getType(void) const override;

    private:
        Math::Point3D   _position;
        double          _diffuseMultiplier;
};