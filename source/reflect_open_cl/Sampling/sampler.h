/*!
 \file sampler.h
 \author takemura
 */

#ifndef _REFLECT_SAMPLER_H_
#define _REFLECT_SAMPLER_H_

#ifdef REFLECT_XSADD_SAMPLER
#include "xsadd_sampler.h"
typedef XsaddSamplerState SamplerState;
#elif REFLECT_XORSHIFT_SAMPLER
#include "xorshift_sampler.h"
typedef XorshiftSamplerState SamplerState;
#endif /* REFLECT_XORSHIFT_SAMPLER */

/*! \brief Generate floating point number x (0.0 <= x < 1.0) */
float sample(SamplerState* sampler);

#endif /* _REFLECT_SAMPLER_H_ */
