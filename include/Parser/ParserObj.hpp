/*
** EPITECH PROJECT, 2024
** ParserObj
** File description:
** Raytracer
*/

#pragma once

#include "Primitives/Mesh.hpp"
#include "Primitives/Triangle.hpp"
#include "Primitives/IPrimitive.hpp"

#include <tuple>
#include <string>
#include <vector>
#include <memory>
#include <exception>

namespace Raytracer
{
   class ParserObj;
};

class Raytracer::ParserObj {

    public:

        ParserObj(const std::string& filePath, std::shared_ptr<Primitive::Mesh> mesh);
        ~ParserObj() = default;

        bool isVertex(std::string line);
        bool isFace(std::string line);

        void readVertex(std::string line);
        std::tuple<double, double, double, bool> parseVertex(std::string line);

        void readFace(std::string line);
        std::tuple<int, int, int, bool> parseFace(std::string line);

        void createMesh(void);

        class ParserObjException : public std::exception {

            public:

                /**
                 * @brief Exception to throw when there is an error in parsing.
                 *
                 * @param msg to throw
                 */
                explicit ParserObjException(const std::string &msg) : message(msg) {}

                /**
                 * @brief Return the error message.
                 *
                 * @return const char* message
                 */
                virtual const char* what() const noexcept override {
                    return message.c_str();
                }

            private:

                std::string message;
        };

    private:

        std::string                                             _filePath;
        std::shared_ptr<Primitive::Mesh>                        _mesh;
        std::vector<std::tuple<double, double, double, bool>>   _vertexes;
        std::vector<std::tuple<int, int, int, bool>>   _faces;
};
