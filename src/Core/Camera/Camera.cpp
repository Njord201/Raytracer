/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** Raytracer
*/

#include "Camera/Camera.hpp"

Raytracer::Camera::Camera(): _origin(0,0,0), _screen()
{
    this->_resolution.first = 0;
    this->_resolution.second = 0;
    this->_antialiasing = 1;
}

Raytracer::Camera::Camera(const Camera& other)
{
    this->_origin = other._origin;
    this->_screen = other._screen;
    this->_rotation = other._rotation;
    this->_fov = other._fov;
    this->_resolution = other._resolution;
    this->_antialiasing = other._antialiasing;
}

Raytracer::Camera::~Camera()
{
}

Raytracer::Camera::Camera(Math::Point3D _origin, Rectangle3D _screen)
{
    this->_origin = _origin;
    this->_screen = _screen;
}

Raytracer::Ray Raytracer::Camera::ray(double u, double v)
{
    Math::Point3D screen_point = _screen.pointAt(u, v);
    Math::Vector3D direction(screen_point.x() - _origin.x(), screen_point.y() - _origin.y(), screen_point.z() - _origin.z());
    return Raytracer::Ray(_origin, direction);
}

Math::Point3D Raytracer::Camera::getOrigin(void) const
{
    return this->_origin;
}

Raytracer::Rectangle3D Raytracer::Camera::getScreen(void) const
{
    return this->_screen;
}

double Raytracer::Camera::getFov(void) const
{
    return this->_fov;
}

Math::Vector3D Raytracer::Camera::getRotation(void) const
{
    return this->_rotation;
}

std::pair<double, double> Raytracer::Camera::getResolution(void) const
{
    return this->_resolution;
}

void Raytracer::Camera::setOrigin(Math::Point3D origin)
{
    this->_origin = origin;
}

void Raytracer::Camera::setScreen(Raytracer::Rectangle3D screen)
{
    this->_screen = screen;
}

void Raytracer::Camera::setFov(double fov)
{
    this->_fov = fov;
}

void Raytracer::Camera::setRotation(Math::Vector3D rotation)
{
   this->_rotation = rotation;
}

void Raytracer::Camera::setResolution(double width, double height)
{
    this->_resolution.first = width;
    this->_resolution.second = height;
}

Raytracer::Camera& Raytracer::Camera::operator=(const Raytracer::Camera& other)
{
    this->_fov = other.getFov();
    this->_origin = other.getOrigin();
    this->_resolution = other.getResolution();
    this->_rotation = other.getRotation();
    this->_screen = other.getScreen();
    this->_antialiasing = other.getAntialiasing();
    return *this;
}

void Raytracer::Camera::setAntialiasing(int antialiasing)
{
    this->_antialiasing = antialiasing;
}

int Raytracer::Camera::getAntialiasing(void) const
{
    return this->_antialiasing;
}
