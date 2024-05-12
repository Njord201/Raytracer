/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** OctreeRules
*/

#pragma once

#include <utility>

namespace Octree {

    struct cubeCollider {
        std::pair<bool, double> minX;
        std::pair<bool, double> minY;
        std::pair<bool, double> minZ;
        std::pair<bool, double> maxX;
        std::pair<bool, double> maxY;
        std::pair<bool, double> maxZ;
    };
};
