/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** RectangularCuboid
*/

#include "IPrimitive.hpp"

namespace Primitive {

    class RectangularCuboid : public IPrimitive {

        public:

            /**
             * @brief Construct a new RectangularCuboid object.
             *
             */
            RectangularCuboid();

            /**
             * @brief Construct a new RectangularCuboid object.
             *
             * @param maxX double max x of the rectangular cuboid
             * @param maxY double max y of the rectangular cuboid
             * @param maxZ double max z of the rectangular cuboid
             * @param minX double min x of the rectangular cuboid
             * @param minY double min y of the rectangular cuboid
             * @param minZ double min z of the rectangular cuboid
             * @param material Material of the rectangular cuboid
             */
            RectangularCuboid(double maxX, double maxY, double maxZ, double minX, double minY, double minZ, std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Destroy the RectangularCuboid object.
             *
             */
            ~RectangularCuboid() = default;

            /**
             * @brief Return the hit point of the rectangular cuboid.
             *
             * @param ray vector3D
             * @return Point3D
             */
            Math::Point3D hitPoint(const Raytracer::Ray& ray) const override;

            /**
             * @brief Get the min x value.
             *
             * @return double | min x value.
             */
            double getMinX() const;

            /**
             * @brief Get the min y value.
             *
             * @return double | min y value.
             */
            double getMinY() const;

            /**
             * @brief Get the min z value.
             *
             * @return double | min z value.
             */
            double getMinZ() const;

            /**
             * @brief Get the max x value.
             *
             * @return double | max x value.
             */
            double getMaxX() const;

            /**
             * @brief Get the max y value.
             *
             * @return double | max y value.
             */
            double getMaxY() const;

            /**
             * @brief Get the max z value.
             *
             * @return double | max z value.
             */
            double getMaxZ() const;

            /**
             * @brief Set the min x value.
             *
             * @param minX double min x value.
             */
            void setMinX(double minX);

            /**
             * @brief Set the min y value.
             *
             * @param minY double min y value.
             */
            void setMinY(double minY);

            /**
             * @brief Set the min z value.
             *
             * @param minZ double min z value.
             */
            void setMinZ(double minZ);

            /**
             * @brief Set the max x value.
             *
             * @param maxX double max x value.
             */
            void setMaxX(double maxX);

            /**
             * @brief Set the max y value.
             *
             * @param maxY double max y value.
             */
            void setMaxY(double maxY);

            /**
             * @brief Set the max z value.
             *
             * @param maxZ double max z value.
             */
            void setMaxZ(double maxZ);

            /**
             * @brief Get the Material object.
             *
             * @return Material of rectangular cuboid
             */
            std::shared_ptr<Material::IMaterial> getMaterial() const;

            /**
             * @brief Set the Material object.
             *
             * @param material Material of rectangular cuboid
             */
            void setMaterial(std::shared_ptr<Material::IMaterial> material);

            /**
             * @brief Get the Normal of the object.
             *
             * @param hitPoint to have the normal
             * @return Math::Vector3D
             */
            Math::Vector3D getNormal(const Math::Vector3D& hitPoint) const override;

            /**
             * @brief Set the Rotation of the object.
             *
             * @param rotation - Rotation value
             */
            void setRotation(Math::Vector3D rotation);

        private:

            /**
             * @brief Check if the ray reach the primitive rectangular cuboid.
             *
             * @param t - coefficient ((x | y | z) - rayOrigin.(x | y | z) / rayDirection.(x | y | z)
             * @param vDir - vector direction of the ray
             * @param origin - origin of the ray
             * @return hitPoint if the ray reach the primitive or
             * @return (-1, -1, -1) if the ray doesn't reach the primitive
             */
            Math::Point3D checkRayReachPrimitive(double t, Math::Vector3D vDir, Math::Point3D origin) const;

            double                                  _maxX;
            double                                  _minX;
            double                                  _maxY;
            double                                  _minY;
            double                                  _maxZ;
            double                                  _minZ;
            std::shared_ptr<Material::IMaterial>    _material;
            Math::Vector3D                          _rotation;
    };
};
