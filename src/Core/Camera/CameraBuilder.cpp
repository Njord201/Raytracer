/*
** EPITECH PROJECT, 2024
** Camera.cpp
** File description:
** Raytracer
*/

#include "Camera/CameraBuilder.hpp"

Raytracer::CameraBuilder& Raytracer::CameraBuilder::setOrigin(Math::Point3D origin)
{
    this->camera.setOrigin(origin);
    return *this;
}

Raytracer::CameraBuilder& Raytracer::CameraBuilder::setScreen(Raytracer::Rectangle3D screen)
{
    this->camera.setScreen(screen);
    return *this;
}

Raytracer::CameraBuilder& Raytracer::CameraBuilder::setFov(double fov)
{
    this->camera.setFov(fov);
    return *this;
}

Raytracer::CameraBuilder& Raytracer::CameraBuilder::setRotation(Math::Vector3D rotation)
{
   this->camera.setRotation(rotation);
   return *this;
}

Raytracer::CameraBuilder& Raytracer::CameraBuilder::setResolution(double width, double height)
{
    this->camera.setResolution(width, height);
    return *this;
}

Raytracer::Camera Raytracer::CameraBuilder::build(void)
{
    return this->camera;
}
