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

        /**
         * @brief Construct a new parser obj object.
         *
         * @param filePath path to the OBJ file
         * @param mesh to create with the file
         */
        ParserObj(const std::string& filePath, std::shared_ptr<Primitive::Mesh> mesh);

        /**
         * @brief Destroy the parser obj object.
         *
         */
        ~ParserObj() = default;

        /**
         * @brief Check if a string start by 'v'.
         *
         * @param line to check
         * @return true
         * @return false
         */
        bool isVertex(std::string line);

        /**
         * @brief Check if a string start by 'f'.
         *
         * @param line to check
         * @return true
         * @return false
         */
        bool isFace(std::string line);

        /**
         * @brief Read a vertex line.
         *
         * @param line to read
         */
        void readVertex(std::string line);

        /**
         * @brief Parse a vertex line.
         *
         * @param line to parse
         * @return std::tuple<double, double, double, bool> line parsed
         */
        std::tuple<double, double, double, bool> parseVertex(std::string line);

        /**
         * @brief Read a face line.
         *
         * @param line to read
         */
        void readFace(std::string line);

        /**
         * @brief Parse a face line.
         *
         * @param line to parse
         * @return std::tuple<int, int, int, bool> line parsed
         */
        std::tuple<int, int, int, bool> parseFace(std::string line);

        /**
         * @brief Create a Mesh object with the parsing done.
         *
         */
        void createMesh(void);

        /**
         * @brief Class exception for the ParserObj
         *
         */
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
        std::vector<std::tuple<int, int, int, bool>>            _faces;
};
