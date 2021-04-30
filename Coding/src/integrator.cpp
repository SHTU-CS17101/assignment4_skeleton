#ifndef NO_OMP
#include <omp.h>
#endif
#include "progressbar.hpp"
#include "integrator.hpp"
#include "constant.hpp"
#include "light.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "brdf.hpp"



extern Config conf;


/**
 * Integrator class
 */

Integrator::Integrator(Scene* scn, Camera* cam)
    : scene(scn)
    , camera(cam)
{
}


/**
 * PathTracingIntegrator class
 */

PathTracingIntegrator::PathTracingIntegrator(Scene* scene, Camera* camera)
    : Integrator(scene, camera)
{  
}

void PathTracingIntegrator::render()
{
    int dx, dy;
    int res_x = camera->getFilm().resolution.x(), res_y = camera->getFilm().resolution.y();

    /* Initialize a progress bar */
    progressbar progress_bar(res_x * res_y);

#ifndef NO_OMP
    #pragma omp parallel for private(dy)
#endif
    for (dx = 0; dx < res_x; ++dx)
    {
        for (dy = 0; dy < res_y; ++dy)
        {
            
            /** TODO */
            UNREACHABLE;

#ifndef NO_OMP
            #pragma omp critical
#endif
            progress_bar.update();
        }
    }
}

Eigen::Vector3f PathTracingIntegrator::radiance(Ray ray)
{
    /** TODO */
    UNREACHABLE;
}
