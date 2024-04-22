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

            Vector3D();
            Vector3D(double x, double y, double z);

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
        
        private:

            double _vector[3];

    };
    using Point3D = Vector3D;
};
