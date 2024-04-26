/*
** EPITECH PROJECT, 2024
** Factory
** File description:
** Raytracer
*/

#include "Parser/Factory.hpp"

Raytracer::Factory::Factory()
{
    std::shared_ptr<DLLoader> sphereLoader = std::make_shared<DLLoader>("plugins/raytracer_sphere.so");

    // Primitive::IPrimitive *test = sphereLoader->getInstance<Primitive::IPrimitive *>("getSphereInstance");

    // std::shared_ptr<Primitive::IPrimitive> sharedPtr(test);

    // std::shared_ptr<Primitive::Sphere> spherePtr = std::dynamic_pointer_cast<Primitive::Sphere>(sharedPtr);

    // std::cout << "_origin.x : [" << spherePtr->_origin.x() << "]" << std::endl;

    this->_libraryLoader.push_back(sphereLoader);

    this->registerComponent("sphere", [sphereLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *test = sphereLoader->getInstance<Primitive::IPrimitive *>("getSphereInstance");

        std::shared_ptr<Primitive::IPrimitive> sharedPtr(test);
        return sharedPtr;
    });
}

Raytracer::Factory::~Factory()
{
}

std::shared_ptr<Primitive::IPrimitive> Raytracer::Factory::createComponent(const std::string &type)
{
    auto it = this->_componentPrimitivesList.find(type);
    if (it != _componentPrimitivesList.end()) {
        auto uniquePtr = it->second();
        return uniquePtr;
    } else {
        return NULL;
    }
}

void Raytracer::Factory::registerComponent(const std::string& type, PrimitivesCreator creator)
{
    this->_componentPrimitivesList[type] = creator;
}
