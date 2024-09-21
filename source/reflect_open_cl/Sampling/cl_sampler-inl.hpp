/*!
  \file cl_sampler-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_CL_SAMPLER_INL_HPP_
#define _REFLECT_CL_SAMPLER_INL_HPP_

#include "cl_sampler.hpp"
// Zisc
#include "zisc/xsadd_engin.hpp"
// Reflect
#include "cl_xsadd_sampler.hpp"

namespace reflect {

template <>
struct ClSamplerType<zisc::XsaddEngin>
{
  using type = ClXsaddState;
};

} // namespace reflect

#endif // _REFLECT_CL_SAMPLER_INL_HPP_
