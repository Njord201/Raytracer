/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Math Vector3D
*/

#pragma once

namespace Math {

    /**
     * @brief Vector 3D class (x, y, z)
     * 
     */
    class Vector3D {

        public:

            /**
             * @brief Construct a new Vector 3D object
             *
             */
            Vector3D();

            /**
             * @brief Construct a new Vector 3D object
             * 
             * @param x position vector
             * @param y position vector
             * @param z position vector
             */
            Vector3D(double x, double y, double z);

            /**
             * @brief return x coordinate vector
             * 
             * @return double 
             */
            double x() const;

            /**
             * @brief return y coordinate vector
             * 
             * @return double 
             */
            double y() const;

            /**
             * @brief return z coordinate vector
             * 
             * @return double 
             */
            double z() const;

            /**
             * @brief return the lenght of the vector
             * 
             * @return double 
             */
            double length() const;

            /**
             * @brief return the square lenght of the vector
             * 
             * @return double 
             */
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
