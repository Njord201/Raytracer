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
    this->_libraryLoader.push_back(sphereLoader);
    std::shared_ptr<DLLoader> planeLoader = std::make_shared<DLLoader>("plugins/raytracer_plane.so");
    this->_libraryLoader.push_back(planeLoader);
    std::shared_ptr<DLLoader> ambientLoader = std::make_shared<DLLoader>("plugins/raytracer_ambient.so");
    this->_libraryLoader.push_back(ambientLoader);
    std::shared_ptr<DLLoader> pointLoader = std::make_shared<DLLoader>("plugins/raytracer_point.so");
    this->_libraryLoader.push_back(pointLoader);
    std::shared_ptr<DLLoader> directionalLoader = std::make_shared<DLLoader>("plugins/raytracer_directional.so");
    this->_libraryLoader.push_back(directionalLoader);
    std::shared_ptr<DLLoader> cylinderLoader = std::make_shared<DLLoader>("plugins/raytracer_cylinder.so");
    this->_libraryLoader.push_back(cylinderLoader);
    this->registerPrimitivesComponent("sphere", [sphereLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *sphere = sphereLoader->getInstance<Primitive::IPrimitive *>("getSphereInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrSphere(sphere);
        return sharedPtrSphere;
    });
    this->registerPrimitivesComponent("cylinder", [cylinderLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *cylinder = cylinderLoader->getInstance<Primitive::IPrimitive *>("getCylinderInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrCylinder(cylinder);
        return sharedPtrCylinder;
    });
    this->registerPrimitivesComponent("plane", [planeLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *plane = planeLoader->getInstance<Primitive::IPrimitive *>("getInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrPlane(plane);
        return sharedPtrPlane;
    });
    this->registerLightsComponent("ambient", [ambientLoader]() -> std::shared_ptr<Light::ILight> {
        Light::ILight *ambient = ambientLoader->getInstance<Light::ILight *>("getAmbientInstance");
        std::shared_ptr<Light::ILight> sharedPtrAmbient(ambient);
        return sharedPtrAmbient;
    });
    this->registerLightsComponent("point", [pointLoader]() -> std::shared_ptr<Light::ILight> {
        Light::ILight *point = pointLoader->getInstance<Light::ILight *>("getPointInstance");
        std::shared_ptr<Light::ILight> sharedPtrPoint(point);
        return sharedPtrPoint;
    });
    this->registerLightsComponent("directional", [directionalLoader]() -> std::shared_ptr<Light::ILight> {
        Light::ILight *directional = directionalLoader->getInstance<Light::ILight *>("getDirectionalInstance");
        std::shared_ptr<Light::ILight> sharedPtrDirectional(directional);
        return sharedPtrDirectional;
    });
}

std::shared_ptr<Primitive::IPrimitive> Raytracer::Factory::createPrimitivesComponent(const std::string &type)
{
    auto it = this->_componentPrimitivesList.find(type);
    if (it != _componentPrimitivesList.end()) {
        auto uniquePtr = it->second();
        return uniquePtr;
    } else {
        return NULL;
    }
}

void Raytracer::Factory::registerPrimitivesComponent(const std::string& type, PrimitivesCreator creator)
{
    this->_componentPrimitivesList[type] = creator;
}

std::shared_ptr<Light::ILight> Raytracer::Factory::createLightsComponent(const std::string &type)
{
    auto it = this->_componentLightsList.find(type);
    if (it != _componentLightsList.end()) {
        auto uniquePtr = it->second();
        return uniquePtr;
    } else {
        return NULL;
    }
}

void Raytracer::Factory::registerLightsComponent(const std::string& type, LightsCreator creator)
{
    this->_componentLightsList[type] = creator;
}
