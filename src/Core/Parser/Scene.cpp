/*
** EPITECH PROJECT, 2024
** Scene
** File description:
** Raytracer
*/

#include "Parser/Scene.hpp"

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
        Math::Vector3D neworigin = this->_camera.getOrigin();
        neworigin.translate(trans);
        this->_camera.setOrigin(neworigin);
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
                Math::Vector3D neworigin = newSphere->getOrigin();
                neworigin.translate(trans);
                newSphere->setOrigin(neworigin);
            }

            this->_primitives.add(newSphere);
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
                Math::Vector3D neworigin = newPoint->getPosition();
                neworigin.translate(trans);
                newPoint->setPosition(neworigin);
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
                Math::Vector3D neworigin = newDirectional->getPosition();
                neworigin.translate(trans);
                newDirectional->setPosition(neworigin);
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
