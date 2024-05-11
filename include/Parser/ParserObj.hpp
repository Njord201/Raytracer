/*
** EPITECH PROJECT, 2024
** ParserObj
** File description:
** Raytracer
*/

#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Primitives/Mesh.hpp"

#include <string>
#include <memory>

namespace Raytracer
{
   class ParserObj;
};

class Raytracer::ParserObj {

    public:

        ParserObj(const std::string& filePath, std::shared_ptr<Primitive::Mesh> mesh);
        ~ParserObj() = default;

    private:

        std::string                         _filePath;
        std::shared_ptr<Primitive::Mesh>    _mesh;
};
