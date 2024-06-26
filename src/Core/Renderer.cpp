/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"

#include <cmath>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Raytracer::Renderer::Renderer(Raytracer::Scene scene) : _camera(scene.getCamera())
{
    _lights = scene.getLights();
    _primitives = scene.getPrimitives();
    Optimisation::cubeCollider collider = {{false, -500}, {false, -500}, {false, -500}, {false, 500}, {false, 500}, {false, 500}};
    _octree = Optimisation::Octree(_primitives, collider);
}

void Raytracer::Renderer::writeColor(std::ostream& o, const Color& color)
{
    int r = int(color.getR());
    int g = int(color.getG());
    int b = int(color.getB());

    o << r << ' ' << g << ' ' << b << '\n';
}

void Raytracer::Renderer::renderScene()
{
    renderFinalScene();

    double imageWidth = _camera.getResolution().first;
    double imageHeight = _camera.getResolution().second;

    // SDL init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Window* win;
    SDL_Renderer* ren;
    SDL_CreateWindowAndRenderer((int)imageWidth, (int)imageHeight, 0, &win, &ren);
    SDL_Event event;

    SDL_Surface *surface = IMG_Load("output.ppm");
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surface);

    bool windowOpen = true;
    while (windowOpen) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                windowOpen = false;
        }
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, nullptr, nullptr);
        SDL_RenderPresent(ren);
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void Raytracer::Renderer::renderFinalScene()
{
    std::ofstream stream("output.ppm");

    int supersamplingFactor = _camera.getAntialiasing();

    // Image Resolution
    double imageWidth = _camera.getResolution().first;
    double imageHeight = _camera.getResolution().second;

    double supersampledWidth = imageWidth * supersamplingFactor;
    double supersampledHeight = imageHeight * supersamplingFactor;

    auto imageRatio = supersampledWidth / supersampledHeight;

    // Field of view in degrees
    double fov = _camera.getFov();
    auto focalLength = 1.0;
    auto viewHeight = 2.0 * std::tan((fov * M_PI / 180.0) / 2.0) * focalLength;
    auto viewWidth = viewHeight * imageRatio;

    std::vector<std::vector<Color>> supersampledImage(supersampledHeight, std::vector<Color>(supersampledWidth));

    // Calculate the vectors across the horizontal and vertical viewport edges.
    auto viewU = Math::Vector3D(viewWidth, 0, 0);
    auto viewV = Math::Vector3D(0, -viewHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixelSizeU = viewU / supersampledWidth;
    auto pixelSizeV = viewV / supersampledHeight;

    // Calculate the location of the upper-left pixel.
    auto viewUpper_left = _camera.getOrigin() - Math::Vector3D(0, 0, focalLength) - viewU / 2 - viewV / 2;

    for (int y = supersampledHeight - 1; y >= 0; y--) {
        for (int x = 0; x < supersampledWidth; x++) {
            auto pixelCenter = viewUpper_left + (pixelSizeU * (x + 0.5)) + (pixelSizeV * (y + 0.5));
            auto rayDirection = _camera.getOrigin() - pixelCenter;

            rayDirection.rotateX(this->_camera.getRotation().x());
            rayDirection.rotateY(this->_camera.getRotation().y());
            rayDirection.rotateZ(this->_camera.getRotation().z());

            Raytracer::Ray ray(_camera.getOrigin(), rayDirection);
            auto primitives = _octree.getPrimitivesHits(ray);
            Color hit = primitives.getColorPoint(ray, _lights);

            supersampledImage[y][x] = hit;
        }
    }

    std::vector<std::vector<Color>> finalImage(imageHeight, std::vector<Color>(imageWidth));

    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            Color averageColor(0, 0, 0);
            int pixelCount = 0;

            for (int supersamplingY = 0; supersamplingY < supersamplingFactor; supersamplingY++) {
                for (int supersamplingX = 0; supersamplingX < supersamplingFactor; supersamplingX++) {
                    int sourceY = y * supersamplingFactor + supersamplingY;
                    int sourceX = x * supersamplingFactor + supersamplingX;
                    averageColor += supersampledImage[sourceY][sourceX];
                    pixelCount++;
                }
            }

            averageColor /= pixelCount;
            finalImage[y][x] = averageColor;
        }
    }


    if (stream.is_open()) {

        stream << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
        for (int y = imageHeight - 1; y >= 0; y--) {
            for (int x = imageWidth - 1; x >= 0; x--) {
                writeColor(stream, finalImage[y][x]);
            }
        }
    }
}
