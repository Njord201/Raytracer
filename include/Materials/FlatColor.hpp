/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** FlatColor
*/

#pragma once

#include "Materials/IMaterial.hpp"

class FlatColor : public Material::IMaterial {

    public:
        /**
         * @brief Construct a new FlatColor object
         *
         */
        FlatColor();

        /**
         * @brief Construct a new Sphere object
         *
         * @param r r color
         * @param g g color
         * @param b b color
         */
        FlatColor(int r, int g, int b);
        
        /**
         * @brief Destruct a FlatColor object
         *
         */
        ~FlatColor();

        /**
         * @brief Get type of Material
         * @return The type of the material
         */
        Material::MaterialType getType(void) override;

        /**
         * @brief Set the new R color
         * @param r new r color
         */
        void setR(int r);

        /**
         * @brief Set the new G color
         * @param g new g color
         */
        void setG(int g);

        /**
         * @brief Set the new B color
         * @param b new g color
         */
        void setB(int b);

        /**
         * @brief Get the R color
         * @return R color
         */
        int getR(void);

        /**
         * @brief Get the G color
         * @return G color
         */
        int getG(void);

        /**
         * @brief Get the B color
         * @return B color
         */
        int getB(void);

    private:
        int _r;
        int _g;
        int _b;
};
