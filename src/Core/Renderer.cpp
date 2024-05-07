/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>

Raytracer::Renderer::Renderer(Raytracer::Scene scene) : _camera(scene.getCamera())
{
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

void Raytracer::Renderer::renderScene()
{
    // Image Resolution
    double imageWidth = _camera.getResolution().first;
    double imageHeight = _camera.getResolution().second;
    auto imageRatio = imageWidth / imageHeight;

    // Field of view in degrees
    double fov = _camera.getFov();
    auto focalLength = 1.0;
    auto viewHeight = 2.0 * std::tan((fov * M_PI / 180.0) / 2.0) * focalLength;
    auto viewWidth = viewHeight * imageRatio;

    // Calculate the vectors across the horizontal and vertical viewport edges.
    auto viewU = Math::Vector3D(viewWidth, 0, 0);
    auto viewV = Math::Vector3D(0, -viewHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixelSizeU = viewU / imageWidth;
    auto pixelSizeV = viewV / imageHeight;

    // Calculate the location of the upper-left pixel.
    auto viewUpper_left = _camera.getOrigin() - Math::Vector3D(0, 0, focalLength) - viewU / 2 - viewV / 2;

    // SDL init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_CreateWindowAndRenderer((int)imageWidth, (int)imageHeight, 0, &win, &ren);
    SDL_Event event;

    bool windowOpen = true;
    while (windowOpen) {

        SDL_RenderClear(ren);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                windowOpen = false;
        }

        for (int y = imageHeight; y >= 0; y--) {
            for (int x = 0; x < imageWidth; x++) {
                auto invertedX = imageWidth - x - 1;
                auto pixel_center = viewUpper_left + (pixelSizeU * (invertedX + 0.5)) + (pixelSizeV * (y + 0.5));
                auto rayDirection = _camera.getOrigin() - pixel_center;

                Raytracer::Ray r(_camera.getOrigin(), rayDirection);
                Math::Point3D hit = _primitives.hitPoint(r, _lights);

                SDL_SetRenderDrawColor(ren, hit.x(), hit.y(), hit.z(), 255);
                SDL_RenderDrawPoint(ren, x, y);
            }
        }
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void Raytracer::Renderer::renderFinalScene()
{
    std::ofstream stream("output.ppm");

    // Image Resolution
    double imageWidth = _camera.getResolution().first;
    double imageHeight = _camera.getResolution().second;
    auto imageRatio = imageWidth / imageHeight;

    // Field of view in degrees
    double fov = _camera.getFov();
    auto focalLength = 1.0;
    auto viewHeight = 2.0 * std::tan((fov * M_PI / 180.0) / 2.0) * focalLength;
    auto viewWidth = viewHeight * imageRatio;

    // Calculate the vectors across the horizontal and vertical viewport edges.
    auto viewU = Math::Vector3D(viewWidth, 0, 0);
    auto viewV = Math::Vector3D(0, -viewHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixelSizeU = viewU / imageWidth;
    auto pixelSizeV = viewV / imageHeight;

    // Calculate the location of the upper-left pixel.
    auto viewUpper_left = _camera.getOrigin() - Math::Vector3D(0, 0, focalLength) - viewU / 2 - viewV / 2;

    if (stream.is_open()) {

        stream << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int y = imageHeight; y >= 0; y--) {
            for (int x = 0; x < imageWidth; x++) {
                auto invertedX = imageWidth - x - 1;
                auto pixel_center = viewUpper_left + (pixelSizeU * (invertedX + 0.5)) + (pixelSizeV * (y + 0.5));
                auto rayDirection = _camera.getOrigin() - pixel_center;

                Raytracer::Ray r(_camera.getOrigin(), rayDirection);
                Math::Point3D hit = _primitives.hitPoint(r, _lights);
                writeColor(stream, hit);
            }
        }
    }
}
