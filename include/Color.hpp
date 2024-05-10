/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color
*/

#pragma once

#include "Math/Vector3D.hpp"

class Color {

    public:

        /**
         * @brief Construct a new Color object.
         *
         * @param r red value
         * @param g green value
         * @param b blue value
         */
        Color(double r, double g, double b);

        /**
         * @brief Construct a new Color object form a Point3D.
         *
         * @param color
         */
        Color(Math::Point3D color);

        /**
         * @brief Construct a new Color object with default values (black, (0, 0, 0)).
         *
         */
        Color() = default;

        /**
         * @brief Destroy the Color object.
         *
         */
        ~Color() = default;

        /**
         * @brief Set the red value.
         *
         * @param r red value
         */
        void setR(double r);

        /**
         * @brief Get the red value.
         *
         * @return double - red value
         */
        double getR() const;

        /**
         * @brief Set the green value.
         *
         * @param g green value
         */
        void setG(double g);

        /**
         * @brief Get the green value.
         *
         * @return double - green value
         */
        double getG() const;

        /**
         * @brief Set the blue value.
         *
         * @param b blue value
         */
        void setB(double b);

        /**
         * @brief Get the blue value.
         *
         * @return double - blue value
         */
        double getB() const;

        /**
         * @brief Check if the rgb is valid (0 <= rgb <= 255).
         *
         * @return true
         * @return false
         */
        bool isWrongColor() const;

        Color& operator+=(const Color& other);
        Color& operator/=(float value);

    private:
        double _r;
        double _g;
        double _b;

};
