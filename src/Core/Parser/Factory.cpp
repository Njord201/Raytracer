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
    std::shared_ptr<DLLoader> coneLoader = std::make_shared<DLLoader>("plugins/raytracer_cone.so");
    this->_libraryLoader.push_back(coneLoader);
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
    std::shared_ptr<DLLoader> triangleLoader = std::make_shared<DLLoader>("plugins/raytracer_triangle.so");
    this->_libraryLoader.push_back(triangleLoader);
    std::shared_ptr<DLLoader> rectangularCuboidLoader = std::make_shared<DLLoader>("plugins/raytracer_rectangular_cuboid.so");
    this->_libraryLoader.push_back(rectangularCuboidLoader);
    std::shared_ptr<DLLoader> meshLoader = std::make_shared<DLLoader>("plugins/raytracer_mesh.so");
    this->_libraryLoader.push_back(meshLoader);

    this->registerPrimitivesComponent("sphere", [sphereLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *sphere = sphereLoader->getInstance<Primitive::IPrimitive *>("getSphereInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrSphere(sphere);
        return sharedPtrSphere;
    });
    this->registerPrimitivesComponent("cone", [coneLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *cone = coneLoader->getInstance<Primitive::IPrimitive *>("getConeInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrCone(cone);
        return sharedPtrCone;
    });
    this->registerPrimitivesComponent("triangle", [triangleLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *triangle = triangleLoader->getInstance<Primitive::IPrimitive *>("getTriangleInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrTriangle(triangle);
        return sharedPtrTriangle;
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
    this->registerPrimitivesComponent("rectangular_cuboid", [rectangularCuboidLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *rectangularCuboid = rectangularCuboidLoader->getInstance<Primitive::IPrimitive *>("getRectangularCuboidInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrRectangularCuboid(rectangularCuboid);
        return sharedPtrRectangularCuboid;
    });
    this->registerPrimitivesComponent("mesh", [meshLoader]() -> std::shared_ptr<Primitive::IPrimitive> {
        Primitive::IPrimitive *mesh = meshLoader->getInstance<Primitive::IPrimitive *>("getMeshInstance");
        std::shared_ptr<Primitive::IPrimitive> sharedPtrMesh(mesh);
        return sharedPtrMesh;
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
