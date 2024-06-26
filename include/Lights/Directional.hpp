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
         * @param position Position of Directionnal Light
         * @param direction Direction of Directionnal Light
         * @param diffuseMultiplier Diffuse Multiplier of Directionnal Light
         */
        Directional(Math::Point3D position, Math::Vector3D direction, double diffuseMultiplier);

        /**
         * @brief Destroy the Directional object
         *
         */
        ~Directional() = default;

        /**
         * @brief Get the Position number of Point light
         *
         * @return Math::Point3D position
         */
        Math::Point3D getPosition(void) const;

        /**
         * @brief Set the Position object
         *
         * @param position New position of Directional Light
         */
        void setPosition(Math::Point3D position);

        /**
         * @brief Get the Direction number of Point light
         *
         * @return Math::Vector3D direction
         */
        Math::Vector3D getDirection(void) const;

        /**
         * @brief Set the Direction object
         *
         * @param direction New Direction of Directional Light
         */
        void setDirection(Math::Vector3D direction);

        /**
         * @brief Set the Color object.
         *
         * @param rgb color
         */
        void setColor(const Color& rgb);

        /**
         * @brief Get the Diffuse Multiplier number of Point light
         *
         * @return double
         */
        double getDiffuseMultiplier(void) const;

        /**
         * @brief Set the Diffuse Multiplier object
         *
         * @param diffuseMultiplier New Diffuse Multiplier of Directional Light
         */
        void setDiffuseMultiplier(double diffuseMultiplier);

        /**
         * @brief Get type of Light
         *
         * @return The type of the light
         */
        Light::LightType getType(void) const override;

        /**
         * @brief Get the Color object.
         *
         * @return Color
         */
        Color getColor(void) const override;

        /**
         * @brief compute the color point with directional light
         *
         * @param primitiveNormal normal to the hitpoint
         * @param hitPoint hitpoint
         * @param color color
         * @param shadow Primitive::Shadow class to handle shadows
         *
         * @return Math::Point3D color
         */
        Color computeColor(Math::Vector3D primitiveNormal, const Math::Point3D& hitPoint, Math::Point3D color, const Primitives::Shadow& shadow) const override;

    private:
        Math::Point3D    _position;
        Math::Vector3D   _direction;
        double           _diffuseMultiplier;
        Color            _color;
};
