#include <vector>
#include "Eigen/Dense"
#include "interaction.hpp"
#include "utils.hpp"
#include "constant.hpp"
#include "brdf.hpp"


/**
 * BRDF class
 */

BRDF::BRDF()
{
}


/**
 * IdealDiffusion class
 */

IdealDiffusion::IdealDiffusion(Eigen::Vector3f diff)
    : reflectivity(diff)
{
}
    
Eigen::Vector3f IdealDiffusion::eval(const Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

float IdealDiffusion::samplePdf(const Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

float IdealDiffusion::sample(Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

bool IdealDiffusion::isDelta() const
{
    return false;
}


/**
 * IdealSpecular class
 */

IdealSpecular::IdealSpecular(Eigen::Vector3f spec)
    : reflectivity(spec)
{
}

Eigen::Vector3f IdealSpecular::eval(const Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

float IdealSpecular::samplePdf(const Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

float IdealSpecular::sample(Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

bool IdealSpecular::isDelta() const
{
    return true;
}


/**
 * IdealTransmission class
 */

IdealTransmission::IdealTransmission(Eigen::Vector3f reflect, float idx_refract)
    : reflectivity(reflect)
    , ior(idx_refract)
{

}

Eigen::Vector3f IdealTransmission::eval(const Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

float IdealTransmission::samplePdf(const Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

float IdealTransmission::sample(Interaction& interact)
{
    /** TODO */
    UNREACHABLE;
}

bool IdealTransmission::isDelta() const
{
    return true;
}
