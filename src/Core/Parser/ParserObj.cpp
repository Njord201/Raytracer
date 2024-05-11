/*
** EPITECH PROJECT, 2024
** ParserObj
** File description:
** Raytracer
*/

#include "Parser/ParserObj.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

Raytracer::ParserObj::ParserObj(const std::string& filePath, std::shared_ptr<Primitive::Mesh> mesh)
: _filePath(filePath), _mesh(mesh)
{
    std::ifstream file(_filePath);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {

            if (isVertex(line))
                readVertex(line);
            else if (isFace(line))
                readFace(line);
        }
    } else {
        throw ParserObjException("error while opening: " + _filePath);
    }
    file.close();
    this->createMesh();
}

bool Raytracer::ParserObj::isVertex(std::string line)
{
    if (line.substr(0,2)=="v ")
        return true;
    return false;
}

bool Raytracer::ParserObj::isFace(std::string line)
{
    if (line.substr(0,2)=="f ")
        return true;
    return false;
}

void Raytracer::ParserObj::readVertex(std::string line)
{
    std::tuple<double, double, double, bool> vertex = parseVertex(line);
    if (!std::get<3>(vertex))
        return;
    _vertexes.push_back(vertex);
}

std::tuple<double, double, double, bool> Raytracer::ParserObj::parseVertex(std::string line)
{
    std::istringstream vertex(line.substr(2));
    double x,y,z;

    vertex>>x;
    vertex>>y;
    vertex>>z;

    if (vertex.fail())
        return std::tuple<double, double, double, bool>(0,0,0,false);
    return std::tuple<double, double, double, bool>(x,y,z,true);
}

void Raytracer::ParserObj::readFace(std::string line)
{
    std::tuple<int, int, int, bool> face = parseFace(line);
    if (!std::get<3>(face))
        return;
    _faces.push_back(face);
}

std::tuple<int, int, int, bool> Raytracer::ParserObj::parseFace(std::string line)
{
    std::istringstream face(line.substr(2));
    int x,y,z;

    face>>x;
    face>>y;
    face>>z;

    if (face.fail())
        return std::tuple<int, int, int, bool>(0,0,0,false);
    return std::tuple<int, int, int, bool>(x,y,z,true);
}

void Raytracer::ParserObj::createMesh(void)
{
    for (size_t face = 0; face < _faces.size(); face++) {


        if ((int)_vertexes.size() >= std::get<0>(_faces[face]) &&
            (int)_vertexes.size() >= std::get<1>(_faces[face]) &&
            (int)_vertexes.size() >= std::get<2>(_faces[face])) {

            Math::Point3D x (std::get<0>(_vertexes[std::get<0>(_faces[face]) - 1]),
                            std::get<1>(_vertexes[std::get<0>(_faces[face]) - 1]),
                            std::get<2>(_vertexes[std::get<0>(_faces[face]) - 1]));
            Math::Point3D y (std::get<0>(_vertexes[std::get<1>(_faces[face]) - 1]),
                            std::get<1>(_vertexes[std::get<1>(_faces[face]) - 1]),
                            std::get<2>(_vertexes[std::get<1>(_faces[face]) - 1]));
            Math::Point3D z (std::get<0>(_vertexes[std::get<2>(_faces[face]) - 1]),
                            std::get<1>(_vertexes[std::get<2>(_faces[face]) - 1]),
                            std::get<2>(_vertexes[std::get<2>(_faces[face]) - 1]));

            std::shared_ptr<Primitive::Triangle> triangle = std::make_shared<Primitive::Triangle>(x,y,z);
            _mesh->add(triangle);
        }
    }
}
