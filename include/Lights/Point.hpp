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
         * @brief Construct a new Point object.
         *
         */
        Point();

        /**
         * @brief Construct a new Point object.
         *
         * @param position Position of Point Light
         * @param diffuseMultiplier Diffuse multiplier of Point Light
         */
        Point(Math::Point3D position, double diffuseMultiplier);

        /**
         * @brief Destroy the Point object.
         *
         */
        ~Point() = default;

        /**
         * @brief Get the Position number of Point light.
         *
         * @return Math::Point3D position
         */
        Math::Point3D getPosition(void) const;

        /**
         * @brief Set the Position object.
         *
         * @param position New position of Point Light
         */
        void setPosition(Math::Point3D position);

        /**
         * @brief Set the Color object.
         *
         * @param rgb color
         */
        void setColor(const Color& rgb);

        /**
         * @brief Get the Diffuse Multiplier number of Point light.
         *
         * @return double
         */
        double getDiffuseMultiplier(void) const;

        /**
         * @brief Set the Diffuse Multiplier object.
         *
         * @param diffuseMultiplier New Diffuse Multiplier of Point Light
         */
        void setDiffuseMultiplier(double diffuseMultiplier);

        /**
         * @brief Get type of Light.
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
         * @brief Compute the color point with ponctual light.
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
        Math::Point3D   _position;
        double          _diffuseMultiplier;
        Color           _color;
};
