/*
** EPITECH PROJECT, 2024
** ParserObj
** File description:
** Raytracer
*/

#include "Parser/ParserObj.hpp"

#include <iostream>

Raytracer::ParserObj::ParserObj(const std::string& filePath, std::shared_ptr<Primitive::Mesh> mesh)
: _filePath(filePath), _mesh(mesh)
{
}
