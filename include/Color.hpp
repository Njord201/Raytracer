/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Color
*/

#pragma once

class Color {

    public:

        /**
         * @brief Construct a new Color object.
         *
         * @param r red value
         * @param g green value
         * @param b blue value
         */
        Color(int r, int g, int b);

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
         */
        void setR(int r);

        /**
         * @brief Get the red value.
         *
         * @return int - red value
         */
        int getR() const;

        /**
         * @brief Set the green value.
         *
         */
        void setG(int g);

        /**
         * @brief Get the green value.
         *
         * @return int - green value
         */
        int getG() const;

        /**
         * @brief Set the blue value.
         *
         */
        void setB(int b);

        /**
         * @brief Get the blue value.
         *
         * @return int - blue value
         */
        int getB() const;

    private:
        int _r;
        int _g;
        int _b;

};
