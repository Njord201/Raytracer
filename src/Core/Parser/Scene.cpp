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
        this->_parseCameraSetting(camera);
        this->_parsePrimitiveSetting(primitives);
        
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

Raytracer::Scene::~Scene()
{
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
        Math::Point3D origin(0, 0, 0);
        const libconfig::Setting &ResolutionWidthSetting = camera["resolution"]["width"];
        const libconfig::Setting &ResolutionHeightSetting = camera["resolution"]["height"];
        Math::Vector3D bottomSide(_parseValue(ResolutionWidthSetting), 0, 0);
        Math::Vector3D leftSide(0, _parseValue(ResolutionHeightSetting), 0);
        Rectangle3D screen(origin, bottomSide, leftSide);
        this->_camera.setScreen(screen);
    } else {
        throw ParserException("There is no resolution data in file !");
    }
    if (camera.exists("position")) {
        const libconfig::Setting &positionX = camera["position"]["x"];
        const libconfig::Setting &positionY = camera["position"]["y"];
        const libconfig::Setting &positionZ = camera["position"]["z"];
        Math::Point3D origin(_parseValue(positionX), _parseValue(positionY), _parseValue(positionZ));
        this->_camera.setOrigin(origin);
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
    if (camera.exists("fieldOfView")) {
        const libconfig::Setting &fieldOfViewSetting = camera["fieldOfView"];
        this->_camera.setFov(_parseValue(fieldOfViewSetting));
    }
    return 0;
}

int Raytracer::Scene::_parsePrimitiveSetting(const libconfig::Setting &primitives)
{
    Raytracer::Factory factory;

    if (primitives.exists("spheres")) {
        for (int index = 0; index < primitives.getLength(); index++) {
            std::shared_ptr<Primitive::IPrimitive> sphere = factory.createComponent("sphere");
            std::shared_ptr<Primitive::Sphere> sphereTest = std::dynamic_pointer_cast<Primitive::Sphere>(sphere);

            
        }
        std::cout << "Sphere Origin X: [" << sphereTest->getOrigin().x() << "]" << std::endl;
        std::cout << "Sphere Origin Y: [" << sphereTest->getOrigin().y() << "]" << std::endl;
        std::cout << "Sphere Origin Z: [" << sphereTest->getOrigin().z() << "]" << std::endl;
    }
    return 0;
}
