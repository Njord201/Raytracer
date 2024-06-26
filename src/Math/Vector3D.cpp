/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Math Vector3D
*/

#include "Math/Vector3D.hpp"
#include <cmath>

using std::sqrt;

Math::Vector3D::Vector3D() : _vector{0,0,0}{}

Math::Vector3D::Vector3D(double x, double y, double z) : _vector{x, y, z}{}

double Math::Vector3D::x() const
{
    return _vector[0];
}

double Math::Vector3D::y() const
{
    return _vector[1];

}
double Math::Vector3D::z() const
{
    return _vector[2];
}

double Math::Vector3D::length() const
{
    return sqrt(length_squared());
}

double Math::Vector3D::length_squared() const
{
    return _vector[0]*_vector[0] + _vector[1]*_vector[1] + _vector[2]*_vector[2];
}

double Math::Vector3D::dot(const Vector3D& ptr)
{
    return (_vector[0] * ptr._vector[0]) + (_vector[1] * ptr._vector[1]) + (_vector[2] * ptr._vector[2]);
}

void Math::Vector3D::translate(const Vector3D& ptr)
{
    *this += ptr;
}

void Math::Vector3D::rotateZ(double degrees) {
    double radians = degrees * M_PI / 180.0;

    double cos_theta = std::cos(radians);
    double sin_theta = std::sin(radians);

    double x = this->_vector[0];
    double y = this->_vector[1];
    double z = this->_vector[2];

    this->_vector[0] = x * cos_theta - y * sin_theta;
    this->_vector[1] = x * sin_theta + y * cos_theta;
    this->_vector[2] = z;
}

void Math::Vector3D::rotateY(double degrees) {
    double radians = degrees * M_PI / 180.0;

    double cos_theta = std::cos(radians);
    double sin_theta = std::sin(radians);

    double x = this->_vector[0];
    double y = this->_vector[1];
    double z = this->_vector[2];

    this->_vector[0] = z * sin_theta + x * cos_theta;
    this->_vector[1] = y;
    this->_vector[2] = z * cos_theta - x * sin_theta;
}

void Math::Vector3D::rotateX(double degrees) {
    double radians = degrees * M_PI / 180.0;

    double cos_theta = std::cos(radians);
    double sin_theta = std::sin(radians);

    double x = this->_vector[0];
    double y = this->_vector[1];
    double z = this->_vector[2];

    this->_vector[0] = x;
    this->_vector[1] = y * cos_theta + z * sin_theta;
    this->_vector[2] = -y * sin_theta + z * cos_theta;
}

Math::Vector3D Math::Vector3D::operator+(const Vector3D& ptr)
{
    return Vector3D(_vector[0] + ptr._vector[0], _vector[1] + ptr._vector[1], _vector[2] + ptr._vector[2]);
}

Math::Vector3D& Math::Vector3D::operator+=(const Vector3D& ptr)
{
    _vector[0] += ptr._vector[0];
    _vector[1] += ptr._vector[1];
    _vector[2] += ptr._vector[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator-(const Vector3D& ptr)
{
    return Vector3D(_vector[0] - ptr._vector[0], _vector[1] - ptr._vector[1], _vector[2] - ptr._vector[2]);
}

Math::Vector3D& Math::Vector3D::operator-=(const Vector3D& ptr)
{
    _vector[0] -= ptr._vector[0];
    _vector[1] -= ptr._vector[1];
    _vector[2] -= ptr._vector[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator*(const Vector3D& ptr)
{
    return Vector3D(_vector[0] * ptr._vector[0], _vector[1] * ptr._vector[1], _vector[2] * ptr._vector[2]);
}

Math::Vector3D& Math::Vector3D::operator*=(const Vector3D& ptr)
{
    _vector[0] *= ptr._vector[0];
    _vector[1] *= ptr._vector[1];
    _vector[2] *= ptr._vector[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator/(const Vector3D& ptr)
{
    return Vector3D(_vector[0] / ptr._vector[0], _vector[1] / ptr._vector[1], _vector[2] / ptr._vector[2]);
}

Math::Vector3D& Math::Vector3D::operator/=(const Vector3D& ptr)
{
    _vector[0] /= ptr._vector[0];
    _vector[1] /= ptr._vector[1];
    _vector[2] /= ptr._vector[2];

    return *this;
}

Math::Vector3D Math::Vector3D::operator*(double n)
{
    return Vector3D(_vector[0] * n, _vector[1] * n, _vector[2] * n);
}

Math::Vector3D& Math::Vector3D::operator*=(double n)
{
    _vector[0] *= n;
    _vector[1] *= n;
    _vector[2] *= n;

    return *this;
}

Math::Vector3D Math::Vector3D::operator/(double n)
{
    return Vector3D(_vector[0] / n, _vector[1] / n, _vector[2] / n);
}

Math::Vector3D& Math::Vector3D::operator/=(double n)
{
    _vector[0] /= n;
    _vector[1] /= n;
    _vector[2] /= n;

    return *this;
}

Math::Vector3D Math::Vector3D::cross(const Vector3D& ptr)
{
    return Math::Vector3D(_vector[1] * ptr._vector[2] - _vector[2] * ptr._vector[1],
                          _vector[2] * ptr._vector[0] - _vector[0] * ptr._vector[2],
                          _vector[0] * ptr._vector[1] - _vector[1] * ptr._vector[0]);
}

bool Math::Vector3D::operator==(const Vector3D& ptr)
{
    return _vector[0] == ptr._vector[0] && _vector[1] == ptr._vector[1] && _vector[2] == ptr._vector[2];
}

bool Math::Vector3D::operator!=(const Vector3D& ptr)
{
    return _vector[0] != ptr._vector[0] || _vector[1] != ptr._vector[1] || _vector[2] != ptr._vector[2];
}

bool Math::Vector3D::operator<(const Vector3D& ptr)
{
    return _vector[0] < ptr._vector[0] && _vector[1] < ptr._vector[1] && _vector[2] < ptr._vector[2];
}

bool Math::Vector3D::operator>(const Vector3D& ptr)
{
    return _vector[0] > ptr._vector[0] && _vector[1] > ptr._vector[1] && _vector[2] > ptr._vector[2];
}
