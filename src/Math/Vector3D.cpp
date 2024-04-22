/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Math Vector3D
*/

#include "Vector3D.hpp"
#include <cmath>

using std::sqrt;

Math::Vector3D::Vector3D() : values{0,0,0}{}

Math::Vector3D::Vector3D(double x, double y, double z) : values{x, y, z}{}

double Math::Vector3D::x() const
{
    return values[0];
}

double Math::Vector3D::y() const
{
    return values[1];

}
double Math::Vector3D::z() const
{
    return values[2];
}

double Math::Vector3D::length() const
{
    return sqrt(length_squared());
}

double Math::Vector3D::length_squared() const
{
    return values[0]*values[0] + values[1]*values[1] + values[2]*values[2];
}

Math::Vector3D Math::Vector3D::operator+(const Vector3D& ptr)
{
    return Vector3D(values[0] + ptr.values[0], values[1] + ptr.values[1], values[2] + ptr.values[2]);
}

Math::Vector3D& Math::Vector3D::operator+=(const Vector3D& ptr)
{
    values[0] += ptr.values[0];
    values[1] += ptr.values[1];
    values[2] += ptr.values[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator-(const Vector3D& ptr)
{
    return Vector3D(values[0] - ptr.values[0], values[1] - ptr.values[1], values[2] - ptr.values[2]);
}

Math::Vector3D& Math::Vector3D::operator-=(const Vector3D& ptr)
{
    values[0] -= ptr.values[0];
    values[1] -= ptr.values[1];
    values[2] -= ptr.values[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator*(const Vector3D& ptr)
{
    return Vector3D(values[0] * ptr.values[0], values[1] * ptr.values[1], values[2] * ptr.values[2]);
}

Math::Vector3D& Math::Vector3D::operator*=(const Vector3D& ptr)
{
    values[0] *= ptr.values[0];
    values[1] *= ptr.values[1];
    values[2] *= ptr.values[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator/(const Vector3D& ptr)
{
    return Vector3D(values[0] / ptr.values[0], values[1] / ptr.values[1], values[2] / ptr.values[2]);
}

Math::Vector3D& Math::Vector3D::operator/=(const Vector3D& ptr)
{
    values[0] /= ptr.values[0];
    values[1] /= ptr.values[1];
    values[2] /= ptr.values[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator*(double n)
{
    return Vector3D(values[0] * n, values[1] * n, values[2] * n);
}

Math::Vector3D& Math::Vector3D::operator*=(double n)
{
    values[0] *= n;
    values[1] *= n;
    values[2] *= n;

    return *this;
}

Math::Vector3D Math::Vector3D::operator/(double n)
{
    return Vector3D(values[0] / n, values[1] / n, values[2] / n);
}

Math::Vector3D& Math::Vector3D::operator/=(double n)
{
    values[0] /= n;
    values[1] /= n;
    values[2] /= n;

    return *this;
}
