/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Math Vector3D
*/

#pragma once

#define IS_INVERSE(X,Y) (((X > 0 && Y < 0) || (X < 0 && Y > 0)) ? true : false)

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

            /**
             * @brief return the dot product with an other Vector
             *
             * @param ptr vector to dot with
             * @return double result of dot product
             */
            double dot(const Vector3D& ptr);

            /**
             * @brief translate a vector with an other
             *
             * @param ptr vector of translation
             */
            void translate(const Vector3D& ptr);

            /**
             * @brief Rotate a vector with an angle on the axis Z.
             * 
             * @param degrees - Rotation value
             */
            void rotateZ(double degrees);

            /**
             * @brief Rotate a vector with an angle on the axis Y.
             * 
             * @param degrees - Rotation value
             */
            void rotateY(double degrees);

            /**
             * @brief Rotate a vector with an angle on the axis X.
             * 
             * @param degrees - Rotation value
             */
            void rotateX(double degrees);

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

            bool operator==(const Vector3D& ptr);
            bool operator!=(const Vector3D& ptr);
            bool operator<(const Vector3D& ptr);
            bool operator>(const Vector3D& ptr);

        private:

            double _vector[3];

    };
    using Point3D = Vector3D;
};
