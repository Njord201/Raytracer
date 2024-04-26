/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <dlfcn.h>
#include <cstring>
#include <iostream>
#include <functional>
#include <libconfig.h++>

namespace Raytracer
{
   class DLLoader;
};

class Raytracer::DLLoader {

    public:
        /**
         * @brief Construct a new DLLoader object
         * @param libraryPath
         */
        DLLoader(const std::string libraryPath);
        
        /**
         * @brief Destroy the DLLoader object
         */
        ~DLLoader();

        /**
         * @brief Get the Instance object
         * @param functionName
         * @return T
         */
        template <typename T>
        T getInstance(const std::string functionName) const
        {
            T (*createInstance)();

            createInstance = (T (*)()) dlsym(_libraryInstance, functionName.c_str());
            if (!createInstance) {
                throw std::runtime_error(dlerror());
            }
            return createInstance();
        }

    protected:
        std::string _libraryPath;
        void *_libraryInstance;
};