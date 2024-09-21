/*!
 \file test.cl
 \author takemura
 */

#include "bvh_node.h"
#include "emitter_model.h"
#include "light_source_reference.h"
#include "object.h"
#include "sampled_wavelengths.h"
#include "surface_scattering_model.h"
#include "spectral_distribution.h"
#include "weight.h"

/*!
 \details
 No detailed.
 */
kernel void sizeTest(global int* result)
{
  result[0] = (int)sizeof(BvhNode);
  result[1] = (int)sizeof(EmitterModel);
  result[2] = (int)sizeof(LightSourceReference);
  result[3] = (int)sizeof(Object);
  result[4] = (int)sizeof(SampledWavelengths);
  result[5] = (int)sizeof(SurfaceScatteringModel);
  result[6] = (int)sizeof(SpectralDistribution);
  result[7] = (int)sizeof(Weight);
}

/*!
 \details
 No detailed.
 */
kernel void initializeFloatTest(global float* result1, global half* result2)
{
  for (size_t index = 0; index < 4; ++index) {
    const float value = (float)index;
    result1[index] = value;
    vstore_half(value, index, result2);
  }
}

/*!
 \details
 No detailed.
 */
kernel void floatTest(global float* result1, global half* result2)
{
  for (size_t index = 0; index < 4; ++index) {
    /* float */
    result1[index] = 2.0f * result1[index];
    /* half */
    const float value = 2.0f * vload_half(index, result2);
    vstore_half(value, index, result2);
  }
}
