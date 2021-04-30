#include <utility>
#include "light.hpp"
#include "geometry.hpp"
#include "utils.hpp"


/**
 * Light class
 */

Light::Light(Eigen::Vector3f pos, Eigen::Vector3f power)
    : position(pos)
    , radiance(power)
{
}

Eigen::Vector3f Light::getPosition() const
{
    return position;
}

Eigen::Vector3f Light::getRadiance() const
{
    return radiance;
}


/**
 * AreaLight class
 */
AreaLight::AreaLight(Eigen::Vector3f pos, Eigen::Vector3f power, Eigen::Vector2f size)
    : Light(pos, power)
    , area_size(size)
    , geometry_delegation(
        pos - Eigen::Vector3f(size[0], 0, size[1]) / 2,
        Eigen::Vector3f(size[0], 0, 0),
        Eigen::Vector3f(0, 0, size[1]),
        Eigen::Vector3f(0, 1, 0), nullptr)
{
}

Eigen::Vector3f AreaLight::emission(Eigen::Vector3f pos, Eigen::Vector3f dir)
{
    /** TODO */
    UNREACHABLE;
}

float AreaLight::samplePdf(const Interaction& ref_it, Eigen::Vector3f pos)
{
    /** TODO */
    UNREACHABLE;
}

Eigen::Vector3f AreaLight::sample(Interaction& ref_it, float* pdf)
{
    /** TODO */
    UNREACHABLE;
}

bool AreaLight::rayIntersection(Interaction& interaction, const Ray& ray)
{
    bool intersection = geometry_delegation.rayIntersection(interaction, ray);
    interaction.type = Interaction::Type::LIGHT;
    return intersection;
}
