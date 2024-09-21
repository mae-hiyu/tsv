/*!
 \file xsadd_sampler.cl
 \author takemura
 */

#include "sampler.h"
#include "xsadd_sampler.h"

/*! \brief Generate random number */
uint generateRandom(XsaddSamplerState* sampler);

/*!  \brief Next sampler state */
uint nextSamplerState(XsaddSamplerState* sampler);

/*!
 \details
 No detailed.
 */
uint generateRandom(XsaddSamplerState* sampler)
{
  return nextSamplerState(sampler);
}

const constant int sh1 = 15;
const constant int sh2 = 18;
const constant int sh3 = 11;

/*!
 \details
 No detailed.
 */
uint nextSamplerState(XsaddSamplerState* sampler)
{
  uint t = sampler->state_[0];
  const uint s3 = sampler->state_[3];
  t ^= t << sh1;
  t ^= t >> sh2;
  t ^= s3 << sh3;

  sampler->state_[0] = sampler->state_[1];
  sampler->state_[1] = sampler->state_[2];
  sampler->state_[2] = sampler->state_[3];
  sampler->state_[3] = t;

  return s3 + t;
}

const constant float normalization_factor = 1.0f / 4294967296.0f;

/*!
 \details
 No detailed.
 */
float sample(XsaddSamplerState* sampler)
{
  return normalization_factor * (float)generateRandom(sampler);
}
