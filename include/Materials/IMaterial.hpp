/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IMaterial
*/

#pragma once

namespace Material {
    class IMaterial;

    typedef enum {
        FlatColor
    } MaterialType;
}

class Material::IMaterial {

    public:

        /**
         * @brief Destroy the IMaterial object
         *
         */
        virtual ~IMaterial() = default;

        /**
         * @brief Get type of Material
         * @return The type of the material
         */
        virtual MaterialType getType(void) = 0;
};
