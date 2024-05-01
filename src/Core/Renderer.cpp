/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"

#include <iostream>
#include <fstream>
#include <cmath>

Raytracer::Renderer::Renderer(Raytracer::Scene scene) : _camera(scene.getCamera())
{
    std::cout << scene.getCamera().getFov() << std::endl;
    _lights = scene.getLights();
    _primitives = scene.getPrimitives();
}

void Raytracer::Renderer::writeColor(std::ostream& o, const Math::Point3D& color)
{
    int r = int(color.x());
    int g = int(color.y());
    int b = int(color.z());

    o << r << ' ' << g << ' ' << b << '\n';
}

void Raytracer::Renderer::renderScene() {
    std::ofstream stream("ok.ppm");

    double fov = 90.0; // Field of view in degrees

    double image_width = _camera.getScreen().getBottomSide().x();
    double image_height = _camera.getScreen().getLeftSide().y();

    auto focal_length = 1.0;
    auto aspect_ratio = image_width / image_height;

    auto viewport_height = 2.0 * std::tan((fov * M_PI / 180.0) / 2.0) * focal_length;

    auto viewport_width = viewport_height * aspect_ratio;

    // Camera setup
    auto camera_center = Math::Point3D(0, 20, -100);

    // Calculate the vectors across the horizontal and vertical viewport edges.
    auto viewport_u = Math::Vector3D(viewport_width, 0, 0);
    auto viewport_v = Math::Vector3D(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper-left pixel.
    auto viewport_upper_left = camera_center
                             - Math::Vector3D(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

    if (stream.is_open()) {
        stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int y = 0; y < image_height; y++) {
            std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
            for (int x = 0; x < image_width; x++) {
                auto pixel_center = viewport_upper_left + (pixel_delta_u * (x + 0.5)) + (pixel_delta_v * (y + 0.5));
                auto ray_direction = pixel_center - camera_center;
                Raytracer::Ray r(camera_center, ray_direction);
                Math::Point3D hit = _primitives.hitPoint(r);
                writeColor(stream, hit);
            }
        }
    }
}