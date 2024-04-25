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
        this->_parseCameraSetting(camera);
        
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


    std::cout << "width: " << "[" << this->_camera.getScreen().getBottomSide().x() << "]" << std::endl;
    std::cout << "height: " << "[" << this->_camera.getScreen().getLeftSide().y() << "]" << std::endl;
    std::cout << "Position X: " << "[" << this->_camera.getOrigin().x() << "]" << std::endl;
    std::cout << "Position Y: " << "[" << this->_camera.getOrigin().y() << "]" << std::endl;
    std::cout << "Position Z: " << "[" << this->_camera.getOrigin().z() << "]" << std::endl;
    std::cout << "Rotation Position X: " << "[" << this->_camera.getRotation().x() << "]" << std::endl;
    std::cout << "Rotation Position Y: " << "[" << this->_camera.getRotation().y() << "]" << std::endl;
    std::cout << "Rotation Position Z: " << "[" << this->_camera.getRotation().z() << "]" << std::endl;
    std::cout << "fov: " << "[" << this->_camera.getFov() << "]" << std::endl;
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
