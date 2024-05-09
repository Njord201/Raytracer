/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#include "Parser/Scene.hpp"

static bool filepathParsed(std::vector<std::string> parsedFiles, std::string filePath)
{
    for (auto &file : parsedFiles) {
        if (file == filePath)
            return true;
    }
    return false;
}

int Raytracer::Scene::parseImportedScene(std::string filePath)
{
    if (filepathParsed(this->_importedScenesFiles, filePath))
        return 0;
    try {
        libconfig::Config cfg;
        cfg.readFile(filePath);
        const libconfig::Setting &primitives = cfg.lookup("primitives");
        const libconfig::Setting &lights = cfg.lookup("lights");
        this->_parsePrimitiveSetting(primitives);
        this->_parseLightsSetting(lights);
        this->_importedScenesFiles.push_back(filePath);
        this->_parseScenesImports(cfg);
    } catch (const libconfig::FileIOException &fioex) {
        throw ParserException("Error reading configuration file.");
    } catch (const libconfig::ParseException &pex) {
        throw ParserException("Error parsing configuration file. Line: " + std::to_string(pex.getLine()) + " - " + pex.getError());
    } catch (const libconfig::SettingTypeException &settingpex) {
        throw ParserException(settingpex.what());
    } catch (const libconfig::SettingNotFoundException &settingpex) {
        throw ParserException(settingpex.what());
    } catch (const ParserException &parseError) {
        throw ParserException(parseError.what());
    }
    return 0;
}

Raytracer::Scene::Scene(std::string filePath)
{
    try {
        libconfig::Config cfg;
        cfg.readFile(filePath);
        const libconfig::Setting &camera = cfg.lookup("camera");
        const libconfig::Setting &primitives = cfg.lookup("primitives");
        const libconfig::Setting &lights = cfg.lookup("lights");
        this->_parseCameraSetting(camera);
        this->_parsePrimitiveSetting(primitives);
        this->_parseLightsSetting(lights);
        this->_importedScenesFiles.push_back(filePath);
        this->_parseScenesImports(cfg);
    } catch (const libconfig::FileIOException &fioex) {
        throw ParserException("Error reading configuration file.");
    } catch (const libconfig::ParseException &pex) {
        throw ParserException("Error parsing configuration file. Line: " + std::to_string(pex.getLine()) + " - " + pex.getError());
    } catch (const libconfig::SettingTypeException &settingpex) {
        throw ParserException(settingpex.what());
    } catch (const libconfig::SettingNotFoundException &settingpex) {
        throw ParserException(settingpex.what());
    } catch (const ParserException &parseError) {
        throw ParserException(parseError.what());
    }
}

int Raytracer::Scene::_parseScenesImports(const libconfig::Config &config)
{
    if (config.exists("imports")) {
        const libconfig::Setting &imports = config.lookup("imports")["scenes"];
        for (int index = 0; index < imports.getLength(); index++) {
            std::string importPath;
            imports[index].lookupValue("path", importPath);
            if (!filepathParsed(this->_importedScenesFiles, importPath)) {
                std::cout << "Importing scene file: " << importPath << std::endl;
                this->parseImportedScene(importPath);
            }
        }
    }
    return 0;
}

double Raytracer::Scene::_parseValue(const libconfig::Setting &value)
{
    double number = 0.0;

    if (value.getType() == libconfig::Setting::TypeFloat) {
        number = value;
    } else {
        int numberInt = value;
        number = static_cast<double>(numberInt);
    }
    return number;
}

int Raytracer::Scene::_parseCameraSetting(const libconfig::Setting &camera)
{
    if (camera.exists("resolution")) {
        const libconfig::Setting &ResolutionWidthSetting = camera["resolution"]["width"];
        const libconfig::Setting &ResolutionHeightSetting = camera["resolution"]["height"];
        this->_camera.setResolution(_parseValue(ResolutionWidthSetting), _parseValue(ResolutionHeightSetting));
    } else {
        throw ParserException("There is no resolution data in file !");
    }
    if (camera.exists("position")) {
        const libconfig::Setting &positionX = camera["position"]["x"];
        const libconfig::Setting &positionY = camera["position"]["y"];
        const libconfig::Setting &positionZ = camera["position"]["z"];
        Math::Point3D origin(_parseValue(positionX), _parseValue(positionY), _parseValue(positionZ));
        this->_camera.setOrigin(origin);

        Math::Vector3D bottomSide(1, 0, 0);
        Math::Vector3D leftSide(0, 1, 0);
        Math::Point3D origin_screen(origin.x() - 0.5, origin.y() - 0.5, 0);
        Rectangle3D screen(origin_screen, bottomSide, leftSide);
        this->_camera.setScreen(screen);
    } else {
        throw ParserException("There is no position data in file !");
    }
    if (camera.exists("rotation")) {
        const libconfig::Setting &rotationX = camera["rotation"]["x"];
        const libconfig::Setting &rotationY = camera["rotation"]["y"];
        const libconfig::Setting &rotationZ = camera["rotation"]["z"];
        Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
        this->_camera.setRotation(rotation);
    }

    if (camera.exists("translation")) {
        libconfig::Setting& translation = camera.lookup("translation");
        Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));
        Math::Vector3D newOrigin = this->_camera.getOrigin();
        newOrigin.translate(trans);
        this->_camera.setOrigin(newOrigin);
    }

    if (camera.exists("fieldOfView")) {
        const libconfig::Setting &fieldOfViewSetting = camera["fieldOfView"];
        this->_camera.setFov(_parseValue(fieldOfViewSetting));
    }
    return 0;
}

int Raytracer::Scene::_parsePrimitiveSetting(const libconfig::Setting &primitives)
{
    if (primitives.exists("spheres")) {
        libconfig::Setting& sphereArray = primitives.lookup("spheres");
        for (int index = 0; index < sphereArray.getLength(); index++) {
            std::shared_ptr<Primitive::IPrimitive> sphere = _factory.createPrimitivesComponent("sphere");
            std::shared_ptr<Primitive::Sphere> newSphere = std::dynamic_pointer_cast<Primitive::Sphere>(sphere);

            const libconfig::Setting &originX = sphereArray[index]["x"];
            const libconfig::Setting &originY = sphereArray[index]["y"];
            const libconfig::Setting &originZ = sphereArray[index]["z"];
            Math::Point3D origin(_parseValue(originX), _parseValue(originY), _parseValue(originZ));

            const libconfig::Setting &radiusValue = sphereArray[index]["r"];
            double radius = _parseValue(radiusValue);

            newSphere->setRadius(radius);
            newSphere->setOrigin(origin);

            if (sphereArray[index].exists("rotation")) {
                libconfig::Setting& rotationSetting = sphereArray[index].lookup("rotation");
                const libconfig::Setting &rotationX = rotationSetting["x"];
                const libconfig::Setting &rotationY = rotationSetting["y"];
                const libconfig::Setting &rotationZ = rotationSetting["z"];
                Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
                newSphere->setRotation(rotation);
            }

            std::string materialType;
            libconfig::Setting& material = sphereArray[index].lookup("material");
            material.lookupValue("type", materialType);

            if (materialType == "flatColor") {
                libconfig::Setting& color = material.lookup("color");
                std::shared_ptr<FlatColor> materialPtr = std::make_shared<FlatColor>(color["r"], color["g"], color["b"]);
                newSphere->setMaterial(materialPtr);
            }

            if (sphereArray[index].exists("translation")) {
                libconfig::Setting& translation = sphereArray[index].lookup("translation");
                Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));
                Math::Vector3D newOrigin = newSphere->getOrigin();
                newOrigin.translate(trans);
                newSphere->setOrigin(newOrigin);
            }
            this->_primitives.add(newSphere);
        }
    }
    if (primitives.exists("cylinders")) {
        libconfig::Setting& cylinderArray = primitives.lookup("cylinders");
        for (int index = 0; index < cylinderArray.getLength(); index++) {
            std::shared_ptr<Primitive::IPrimitive> cylinder = _factory.createPrimitivesComponent("cylinder");
            std::shared_ptr<Primitive::Cylinder> newCylinder = std::dynamic_pointer_cast<Primitive::Cylinder>(cylinder);
            const libconfig::Setting &originX = cylinderArray[index]["x"];
            const libconfig::Setting &originY = cylinderArray[index]["y"];
            const libconfig::Setting &originZ = cylinderArray[index]["z"];
            Math::Point3D origin(_parseValue(originX), _parseValue(originY), _parseValue(originZ));

            const libconfig::Setting &radiusValue = cylinderArray[index]["r"];
            double radius = _parseValue(radiusValue);

            newCylinder->setRadius(radius);
            newCylinder->setOrigin(origin);
            std::string axisType;
            cylinderArray[index].lookupValue("axis", axisType);

            if (axisType == "X") {
                newCylinder->setAxis(Primitive::Axis::X);
            } else if (axisType == "Y") {
                newCylinder->setAxis(Primitive::Axis::Y);
            } else if (axisType == "Z") {
                newCylinder->setAxis(Primitive::Axis::Z);
            } else {
                throw ParserException("Wrong Axis for Cylinder");
            }

            if (cylinderArray[index].exists("rotation")) {
                libconfig::Setting& rotationSetting = cylinderArray[index].lookup("rotation");
                const libconfig::Setting &rotationX = rotationSetting["x"];
                const libconfig::Setting &rotationY = rotationSetting["y"];
                const libconfig::Setting &rotationZ = rotationSetting["z"];
                Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
                newCylinder->setRotation(rotation);
            }
            
            std::string materialType;
            libconfig::Setting& material = cylinderArray[index].lookup("material");
            material.lookupValue("type", materialType);
            if (materialType == "flatColor") {
                libconfig::Setting& color = material.lookup("color");
                std::shared_ptr<FlatColor> materialPtr = std::make_shared<FlatColor>(color["r"], color["g"], color["b"]);
                newCylinder->setMaterial(materialPtr);
            }
            this->_primitives.add(newCylinder);
        }
    }
    if (primitives.exists("cones")) {
        libconfig::Setting& coneArray = primitives.lookup("cones");
        for (int index = 0; index < coneArray.getLength(); index++) {
            std::shared_ptr<Primitive::IPrimitive> cone = _factory.createPrimitivesComponent("cone");
            std::shared_ptr<Primitive::Cone> newCone = std::dynamic_pointer_cast<Primitive::Cone>(cone);

            const libconfig::Setting &originX = coneArray[index]["x"];
            const libconfig::Setting &originY = coneArray[index]["y"];
            const libconfig::Setting &originZ = coneArray[index]["z"];
            Math::Point3D origin(_parseValue(originX), _parseValue(originY), _parseValue(originZ));

            const libconfig::Setting &angleValue = coneArray[index]["angle"];
            double angle = _parseValue(angleValue);

            newCone->setAngle(angle);
            newCone->setOrigin(origin);

            std::string axisType;
            coneArray[index].lookupValue("axis", axisType);

            if (axisType == "X") {
                newCone->setAxis(Primitive::Axis::X);
            } else if (axisType == "Y") {
                newCone->setAxis(Primitive::Axis::Y);
            } else if (axisType == "Z") {
                newCone->setAxis(Primitive::Axis::Z);
            } else {
                throw ParserException("Wrong Axis for plane");
            }

            if (coneArray[index].exists("rotation")) {
                libconfig::Setting& rotationSetting = coneArray[index].lookup("rotation");
                const libconfig::Setting &rotationX = rotationSetting["x"];
                const libconfig::Setting &rotationY = rotationSetting["y"];
                const libconfig::Setting &rotationZ = rotationSetting["z"];
                Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
                newCone->setRotation(rotation);
            }

            std::string materialType;
            libconfig::Setting& material = coneArray[index].lookup("material");
            material.lookupValue("type", materialType);

            if (materialType == "flatColor") {
                libconfig::Setting& color = material.lookup("color");
                std::shared_ptr<FlatColor> materialPtr = std::make_shared<FlatColor>(color["r"], color["g"], color["b"]);
                newCone->setMaterial(materialPtr);
            }

            if (coneArray[index].exists("translation")) {
                libconfig::Setting& translation = coneArray[index].lookup("translation");
                Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));
                Math::Vector3D newOrigin = newCone->getOrigin();
                newOrigin.translate(trans);
                newCone->setOrigin(newOrigin);
            }

            this->_primitives.add(newCone);
        }
    }
    if (primitives.exists("planes")) {
        libconfig::Setting& planeArray = primitives.lookup("planes");
        for (int index = 0; index < planeArray.getLength(); index++) {
            std::shared_ptr<Primitive::IPrimitive> plane = _factory.createPrimitivesComponent("plane");
            std::shared_ptr<Primitive::Plane> newPlane = std::dynamic_pointer_cast<Primitive::Plane>(plane);
            Math::Point3D position(0, 0, 0);

            std::string axisType;
            planeArray[index].lookupValue("axis", axisType);

            if (axisType == "X") {
                newPlane->setAxis(Primitive::Axis::X);
                newPlane->setPosition(Math::Point3D (_parseValue(planeArray[index]["position"]), 0, 0));
            } else if (axisType == "Y") {
                newPlane->setAxis(Primitive::Axis::Y);
                newPlane->setPosition(Math::Point3D (0, _parseValue(planeArray[index]["position"]), 0));
            } else if (axisType == "Z") {
                newPlane->setAxis(Primitive::Axis::Z);
                newPlane->setPosition(Math::Point3D (0, 0, _parseValue(planeArray[index]["position"])));
            } else {
                throw ParserException("Wrong Axis for plane");
            }

            if (planeArray[index].exists("rotation")) {
                libconfig::Setting& rotationSetting = planeArray[index].lookup("rotation");
                const libconfig::Setting &rotationX = rotationSetting["x"];
                const libconfig::Setting &rotationY = rotationSetting["y"];
                const libconfig::Setting &rotationZ = rotationSetting["z"];
                Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
                newPlane->setRotation(rotation);
            }

            std::string materialType;
            libconfig::Setting& material = planeArray[index].lookup("material");
            material.lookupValue("type", materialType);

            if (materialType == "flatColor") {
                libconfig::Setting& color = material.lookup("color");
                std::shared_ptr<FlatColor> materialPtr = std::make_shared<FlatColor>(color["r"], color["g"], color["b"]);
                newPlane->setMaterial(materialPtr);
            }

            this->_primitives.add(newPlane);
        }
    }
    return 0;
}

int Raytracer::Scene::_parseLightsSetting(const libconfig::Setting &lights)
{
    double diffuse = 0.0;
    if (lights.exists("diffuse")) {
        diffuse = this->_parseValue(lights["diffuse"]);
    }
    if (lights.exists("ambient")) {
        std::shared_ptr<Light::ILight> ambient = _factory.createLightsComponent("ambient");
        std::shared_ptr<Light::Ambient> newAmbient = std::dynamic_pointer_cast<Light::Ambient>(ambient);

        newAmbient->setMultiplier(this->_parseValue(lights["ambient"]));
        newAmbient->setDiffuseMultiplier(diffuse);

        this->_lights.add(newAmbient);
    }
    if (lights.exists("point")) {
        libconfig::Setting& lightArrayPoint = lights.lookup("point");
        for (int index = 0; index < lightArrayPoint.getLength(); index++) {
            std::shared_ptr<Light::ILight> point = _factory.createLightsComponent("point");
            std::shared_ptr<Light::Point> newPoint = std::dynamic_pointer_cast<Light::Point>(point);

            const libconfig::Setting &positionX = lightArrayPoint[index]["x"];
            const libconfig::Setting &positionY = lightArrayPoint[index]["y"];
            const libconfig::Setting &positionZ = lightArrayPoint[index]["z"];
            Math::Point3D position(_parseValue(positionX), _parseValue(positionY), _parseValue(positionZ));

            newPoint->setPosition(position);
            newPoint->setDiffuseMultiplier(diffuse);

            if (lightArrayPoint[index].exists("translation")) {
                libconfig::Setting& translation = lightArrayPoint[index].lookup("translation");
                Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));
                Math::Vector3D newOrigin = newPoint->getPosition();
                newOrigin.translate(trans);
                newPoint->setPosition(newOrigin);
            }

            if (lightArrayPoint[index].exists("color")) {
                libconfig::Setting& colorSetting = lightArrayPoint[index].lookup("color");
                Color color(_parseValue(colorSetting["r"]), _parseValue(colorSetting["g"]), _parseValue(colorSetting["b"]));
                newPoint->setColor(color);
            }

            this->_lights.add(newPoint);
        }
    }
    if (lights.exists("directional")) {
        libconfig::Setting& lightArrayDirectional = lights.lookup("directional");
        for (int index = 0; index < lightArrayDirectional.getLength(); index++) {
            std::shared_ptr<Light::ILight> directional = _factory.createLightsComponent("directional");
            std::shared_ptr<Light::Directional> newDirectional = std::dynamic_pointer_cast<Light::Directional>(directional);

            libconfig::Setting& positionSetting = lightArrayDirectional[index].lookup("position");
            const libconfig::Setting &positionX = positionSetting["x"];
            const libconfig::Setting &positionY = positionSetting["y"];
            const libconfig::Setting &positionZ = positionSetting["z"];
            Math::Point3D position(_parseValue(positionX), _parseValue(positionY), _parseValue(positionZ));

            libconfig::Setting& directionSetting = lightArrayDirectional[index].lookup("direction");
            const libconfig::Setting &directionX = directionSetting["x"];
            const libconfig::Setting &directionY = directionSetting["y"];
            const libconfig::Setting &directionZ = directionSetting["z"];
            Math::Point3D direction(_parseValue(directionX), _parseValue(directionY), _parseValue(directionZ));

            newDirectional->setPosition(position);
            newDirectional->setDirection(direction);
            newDirectional->setDiffuseMultiplier(diffuse);

            if (lightArrayDirectional[index].exists("translation")) {
                libconfig::Setting& translation = lightArrayDirectional[index].lookup("translation");
                Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));
                Math::Vector3D newOrigin = newDirectional->getPosition();
                newOrigin.translate(trans);
                newDirectional->setPosition(newOrigin);
            }

            if (lightArrayDirectional[index].exists("color")) {
                libconfig::Setting& colorSetting = lightArrayDirectional[index].lookup("color");
                Color color(_parseValue(colorSetting["r"]), _parseValue(colorSetting["g"]), _parseValue(colorSetting["b"]));
                newDirectional->setColor(color);
            }

            this->_lights.add(newDirectional);
        }
    }
    return 0;
}

Primitive::PrimitivesContainer Raytracer::Scene::getPrimitives(void) const
{
    return this->_primitives;
}

Light::LightsContainer Raytracer::Scene::getLights(void) const
{
    return this->_lights;
}

Raytracer::Camera& Raytracer::Scene::getCamera(void)
{
    return this->_camera;
}
