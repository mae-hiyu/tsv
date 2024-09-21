/*!
 \file camera.h
 \author takemura
 */

#ifndef _REFLECT_CAMERA_H_
#define _REFLECT_CAMERA_H_

#include "ray.h"
#include "sampler.h"

/*! \brief Generate ray */
Ray generateRay(const size_t pixel_index, SamplerState* sampler);

#endif /* _REFLECT_CAMERA_H_ */
