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

// void Raytracer::Renderer::renderScene()
// {
//     std::ofstream stream("ok.ppm");

//     // double image_width = _camera.getScreen().getBottomSide().x();
//     // double image_height = _camera.getScreen().getLeftSide().y();



//     ///////////////////////////////////////////////////////////
//     auto aspect_ratio = 16.0 / 9.0;
//     int image_width = 1920;

//     // Calculate the image height, and ensure that it's at least 1.
//     int image_height = int(image_width / aspect_ratio);
//     image_height = (image_height < 1) ? 1 : image_height;

//     // Camera

//     auto focal_length = 1.0;
//     auto viewport_height = 2.0;
//     auto viewport_width = viewport_height * (double(image_width)/image_height);
//     auto camera_center = Math::Point3D(0, 20, -100);

//     // Calculate the vectors across the horizontal and down the vertical viewport edges.
//     auto viewport_u = Math::Vector3D(viewport_width, 0, 0);
//     auto viewport_v = Math::Vector3D(0, -viewport_height, 0);

//     // Calculate the horizontal and vertical delta vectors from pixel to pixel.
//     auto pixel_delta_u = viewport_u / image_width;
//     auto pixel_delta_v = viewport_v / image_height;

//     // Calculate the location of the upper left pixel.
//     auto viewport_upper_left = camera_center
//                              - Math::Vector3D(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
//     auto pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * 0.5;

//     ///////////////////////////////////////////////////////////

//     if (stream.is_open()) {
//         stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

//         for (int x = 0; x < image_height; x++) {
//             std::clog << "\rScanlines remaining: " << (image_height - x) << ' ' << std::flush;
//             for (int y = 0; y < image_width; y++) {
//                 auto pixel_center = pixel00_loc + (pixel_delta_u * y) + (pixel_delta_v * x);
//                 auto ray_direction = pixel_center - camera_center;
//                 Raytracer::Ray r(camera_center, ray_direction);
//                 Math::Point3D hit = _primitives.hitPoint(r);
//                 writeColor(stream, hit);
//             }
//         }
//     }
//     std::clog << "\rDone.                 \n";
// }


void Raytracer::Renderer::renderScene() {
    double fov = _camera.getFov();
    std::cout << fov << std::endl;
    // std::ofstream stream("ok.ppm");

    // double fov = 72.0; // Field of view in degrees

    // // Calculate the aspect ratio based on the desired field of view.
    // double aspect_ratio = 16.0 / 9.0;

    // // Width of the output image
    // int image_width = 1920;

    // // Calculate the image height based on the aspect ratio and ensure it's at least 1.
    // int image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));

    // // Calculate the viewport height based on the field of view and focal length.
    // auto focal_length = 1.0;
    // auto viewport_height = 2.0 * std::tan((fov * M_PI / 180.0) / 2.0) * focal_length;

    // // Calculate the viewport width based on the aspect ratio.
    // auto viewport_width = viewport_height * aspect_ratio;

    // // Camera setup
    // auto camera_center = Math::Point3D(0, 20, -100);

    // // Calculate the vectors across the horizontal and vertical viewport edges.
    // auto viewport_u = Math::Vector3D(viewport_width, 0, 0);
    // auto viewport_v = Math::Vector3D(0, -viewport_height, 0);

    // // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    // auto pixel_delta_u = viewport_u / image_width;
    // auto pixel_delta_v = viewport_v / image_height;

    // // Calculate the location of the upper-left pixel.
    // auto viewport_upper_left = camera_center
    //                          - Math::Vector3D(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

    // if (stream.is_open()) {
    //     stream << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //     for (int y = 0; y < image_height; y++) {
    //         std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
    //         for (int x = 0; x < image_width; x++) {
    //             auto pixel_center = viewport_upper_left + (pixel_delta_u * (x + 0.5)) + (pixel_delta_v * (y + 0.5));
    //             auto ray_direction = pixel_center - camera_center;
    //             Raytracer::Ray r(camera_center, ray_direction);
    //             // Assuming _primitives.hitPoint returns the hit point on the scene.
    //             Math::Point3D hit = _primitives.hitPoint(r);
    //             // Assuming writeColor writes the color of the hit point to the output stream.
    //             writeColor(stream, hit);
    //         }
    //     }
    // }
}