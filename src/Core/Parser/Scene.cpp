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
        const libconfig::Setting &imports = config.lookup("imports");

        if (imports.exists("scenes")) {
            const libconfig::Setting &scenes = imports.lookup("scenes");
            for (int index = 0; index < scenes.getLength(); index++) {
                std::string importPath;
                scenes[index].lookupValue("path", importPath);
                if (!filepathParsed(this->_importedScenesFiles, importPath)) {
                    std::cout << "Importing scene file: " << importPath << std::endl;
                    this->parseImportedScene(importPath);
                }
            }
        }

        if (imports.exists("meshes")) {
            const libconfig::Setting &meshes = imports.lookup("meshes");
            for (int index = 0; index < meshes.getLength(); index++) {

                std::string meshPath;
                meshes[index].lookupValue("path", meshPath);

                std::shared_ptr<Primitive::IPrimitive> mesh = _factory.createPrimitivesComponent("mesh");
                std::shared_ptr<Primitive::Mesh> newMesh = std::dynamic_pointer_cast<Primitive::Mesh>(mesh);

                std::cout << "Importing obj file: " << meshPath << std::endl;
                ParserObj parserObj(meshPath, newMesh);

                std::string materialType;
                libconfig::Setting& material = meshes[index].lookup("material");
                material.lookupValue("type", materialType);

                if (materialType == "flatColor") {
                    libconfig::Setting& color = material.lookup("color");
                    std::shared_ptr<FlatColor> materialPtr = std::make_shared<FlatColor>(color["r"], color["g"], color["b"]);
                    newMesh->setMaterial(materialPtr);
                }
                this->_primitives.add(newMesh);
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
    CameraBuilder camBuilder;

    if (camera.exists("resolution")) {
        const libconfig::Setting &ResolutionWidthSetting = camera["resolution"]["width"];
        const libconfig::Setting &ResolutionHeightSetting = camera["resolution"]["height"];
        camBuilder.setResolution(_parseValue(ResolutionWidthSetting), _parseValue(ResolutionHeightSetting));
    } else {
        throw ParserException("There is no resolution data in file !");
    }
    if (camera.exists("position")) {
        const libconfig::Setting &positionX = camera["position"]["x"];
        const libconfig::Setting &positionY = camera["position"]["y"];
        const libconfig::Setting &positionZ = camera["position"]["z"];
        Math::Point3D origin(_parseValue(positionX), _parseValue(positionY), _parseValue(positionZ));
        camBuilder.setOrigin(origin);

        Math::Vector3D bottomSide(1, 0, 0);
        Math::Vector3D leftSide(0, 1, 0);
        Math::Point3D origin_screen(origin.x() - 0.5, origin.y() - 0.5, 0);
        Rectangle3D screen(origin_screen, bottomSide, leftSide);
        camBuilder.setScreen(screen);
    } else {
        throw ParserException("There is no position data in file !");
    }
    if (camera.exists("rotation")) {
        const libconfig::Setting &rotationX = camera["rotation"]["x"];
        const libconfig::Setting &rotationY = camera["rotation"]["y"];
        const libconfig::Setting &rotationZ = camera["rotation"]["z"];
        Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
        camBuilder.setRotation(rotation);
    }

    if (camera.exists("translation")) {
        libconfig::Setting& translation = camera.lookup("translation");
        Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));
        Math::Vector3D newOrigin = this->_camera.getOrigin();
        newOrigin.translate(trans);
        camBuilder.setOrigin(newOrigin);
    }

    if (camera.exists("fieldOfView")) {
        const libconfig::Setting &fieldOfViewSetting = camera["fieldOfView"];
        camBuilder.setFov(_parseValue(fieldOfViewSetting));
    }

    if (camera.exists("antialiasing")) {
        const libconfig::Setting &fieldOfViewSetting = camera["antialiasing"];

        if (fieldOfViewSetting.getType() == libconfig::Setting::TypeFloat)
            throw ParserException("Antialiasing must be an Integer and not a Float");
        int number = fieldOfViewSetting;
        if (number <= 0)
            throw ParserException("Antialiasing must be greater than 0");
        camBuilder.setAntialiasing(number);
    }

    this->_camera = camBuilder.build();
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
    if (primitives.exists("triangles")) {

        libconfig::Setting& triangleArray = primitives.lookup("triangles");
        for (int index = 0; index < triangleArray.getLength(); index++) {
            std::shared_ptr<Primitive::IPrimitive> triangle = _factory.createPrimitivesComponent("triangle");
            std::shared_ptr<Primitive::Triangle> newTriangle = std::dynamic_pointer_cast<Primitive::Triangle>(triangle);

            libconfig::Setting& vertex1 = triangleArray[index].lookup("vertex1");
            const libconfig::Setting &vertex1X = vertex1["x"];
            const libconfig::Setting &vertex1Y = vertex1["y"];
            const libconfig::Setting &vertex1Z = vertex1["z"];
            Math::Point3D newVertex1 (_parseValue(vertex1X), _parseValue(vertex1Y), _parseValue(vertex1Z));
            newTriangle->setVertex1(newVertex1);

            libconfig::Setting& vertex2 = triangleArray[index].lookup("vertex2");
            const libconfig::Setting &vertex2X = vertex2["x"];
            const libconfig::Setting &vertex2Y = vertex2["y"];
            const libconfig::Setting &vertex2Z = vertex2["z"];
            Math::Point3D newVertex2 (_parseValue(vertex2X), _parseValue(vertex2Y), _parseValue(vertex2Z));
            newTriangle->setVertex2(newVertex2);

            libconfig::Setting& vertex3 = triangleArray[index].lookup("vertex3");
            const libconfig::Setting &vertex3X = vertex3["x"];
            const libconfig::Setting &vertex3Y = vertex3["y"];
            const libconfig::Setting &vertex3Z = vertex3["z"];
            Math::Point3D newVertex3 (_parseValue(vertex3X), _parseValue(vertex3Y), _parseValue(vertex3Z));
            newTriangle->setVertex3(newVertex3);

            if (triangleArray[index].exists("rotation")) {
                libconfig::Setting& rotationSetting = triangleArray[index].lookup("rotation");
                const libconfig::Setting &rotationX = rotationSetting["x"];
                const libconfig::Setting &rotationY = rotationSetting["y"];
                const libconfig::Setting &rotationZ = rotationSetting["z"];
                Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
                newTriangle->setRotation(rotation);
            }

            std::string materialType;
            libconfig::Setting& material = triangleArray[index].lookup("material");
            material.lookupValue("type", materialType);

            if (materialType == "flatColor") {
                libconfig::Setting& color = material.lookup("color");
                std::shared_ptr<FlatColor> materialPtr = std::make_shared<FlatColor>(color["r"], color["g"], color["b"]);
                newTriangle->setMaterial(materialPtr);
            }

            if (triangleArray[index].exists("translation")) {
                libconfig::Setting& translation = triangleArray[index].lookup("translation");
                Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));
                Math::Vector3D Vertex1Trans = newTriangle->getVertex1();
                Math::Vector3D Vertex2Trans = newTriangle->getVertex2();
                Math::Vector3D Vertex3Trans = newTriangle->getVertex3();
                Vertex1Trans.translate(trans);
                Vertex2Trans.translate(trans);
                Vertex3Trans.translate(trans);
                newTriangle->setVertex1(Vertex1Trans);
                newTriangle->setVertex2(Vertex2Trans);
                newTriangle->setVertex3(Vertex3Trans);
            }
            this->_primitives.add(newTriangle);
        }
    }
    if (primitives.exists("rectangular_cuboids")) {
        libconfig::Setting& rectangularCuboidArray = primitives.lookup("rectangular_cuboids");
        for (int index = 0; index < rectangularCuboidArray.getLength(); index++) {
            std::shared_ptr<Primitive::IPrimitive> rectangularCuboid = _factory.createPrimitivesComponent("rectangular_cuboid");
            std::shared_ptr<Primitive::RectangularCuboid> newRectangularCuboid = std::dynamic_pointer_cast<Primitive::RectangularCuboid>(rectangularCuboid);

            const libconfig::Setting &minX = rectangularCuboidArray[index]["minX"];
            const libconfig::Setting &minY = rectangularCuboidArray[index]["minY"];
            const libconfig::Setting &minZ = rectangularCuboidArray[index]["minZ"];
            const libconfig::Setting &maxX = rectangularCuboidArray[index]["maxX"];
            const libconfig::Setting &maxY = rectangularCuboidArray[index]["maxY"];
            const libconfig::Setting &maxZ = rectangularCuboidArray[index]["maxZ"];

            newRectangularCuboid->setMinX(_parseValue(minX));
            newRectangularCuboid->setMinY(_parseValue(minY));
            newRectangularCuboid->setMinZ(_parseValue(minZ));
            newRectangularCuboid->setMaxX(_parseValue(maxX));
            newRectangularCuboid->setMaxY(_parseValue(maxY));
            newRectangularCuboid->setMaxZ(_parseValue(maxZ));

            std::string materialType;
            libconfig::Setting& material = rectangularCuboidArray[index].lookup("material");
            material.lookupValue("type", materialType);

            if (materialType == "flatColor") {
                libconfig::Setting& color = material.lookup("color");
                std::shared_ptr<FlatColor> materialPtr = std::make_shared<FlatColor>(color["r"], color["g"], color["b"]);
                newRectangularCuboid->setMaterial(materialPtr);
            }

            if (rectangularCuboidArray[index].exists("translation")) {
                libconfig::Setting& translation = rectangularCuboidArray[index].lookup("translation");
                Math::Vector3D trans(_parseValue(translation["x"]), _parseValue(translation["y"]), _parseValue(translation["z"]));

                double newMinX = newRectangularCuboid->getMinX() + trans.x();
                double newMinY = newRectangularCuboid->getMinY() + trans.y();
                double newMinZ = newRectangularCuboid->getMinZ() + trans.z();
                double newMaxX = newRectangularCuboid->getMaxX() + trans.x();
                double newMaxY = newRectangularCuboid->getMaxY() + trans.y();
                double newMaxZ = newRectangularCuboid->getMaxZ() + trans.z();

                newRectangularCuboid->setMinX(newMinX);
                newRectangularCuboid->setMinY(newMinY);
                newRectangularCuboid->setMinZ(newMinZ);
                newRectangularCuboid->setMaxX(newMaxX);
                newRectangularCuboid->setMaxY(newMaxY);
                newRectangularCuboid->setMaxZ(newMaxZ);
            }

            if (rectangularCuboidArray[index].exists("rotation")) {
                libconfig::Setting& rotationSetting = rectangularCuboidArray[index].lookup("rotation");
                const libconfig::Setting &rotationX = rotationSetting["x"];
                const libconfig::Setting &rotationY = rotationSetting["y"];
                const libconfig::Setting &rotationZ = rotationSetting["z"];
                Math::Vector3D rotation(_parseValue(rotationX), _parseValue(rotationY), _parseValue(rotationZ));
                newRectangularCuboid->setRotation(rotation);
            }

            this->_primitives.add(newRectangularCuboid);
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
