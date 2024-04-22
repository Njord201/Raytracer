/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Math Vector3D
*/

#pragma once

namespace Math {

    class Vector3D {
    public:
        double values[3];

        Vector3D();
        Vector3D(double e0, double e1, double e2);

        double x() const;
        double y() const;
        double z() const;

        double length() const;
        double length_squared() const;

        Vector3D operator+(const Vector3D& ptr);
        Vector3D& operator+=(const Vector3D& ptr);
        Vector3D operator-(const Vector3D& ptr);
        Vector3D& operator-=(const Vector3D& ptr);
        Vector3D operator*(const Vector3D& ptr);
        Vector3D& operator*=(const Vector3D& ptr);
        Vector3D operator/(const Vector3D& ptr);
        Vector3D& operator/=(const Vector3D& ptr);

        Vector3D operator*(double n);
        Vector3D& operator*=(double n);
        Vector3D operator/(double n);
        Vector3D& operator/=(double n);
    };
    using Point3D = Vector3D;
};
