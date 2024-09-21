/*!
  \file cl_sampler.cpp
  \author takemura
  */

#include "cl_sampler.hpp"
// Standard C++ library
#include <string>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/utility.hpp"
#include "zisc/xsadd_engin.hpp"
// Reflect
#include "keyword.hpp"
#include "OpenCL/cl.hpp"
#include "OpenCL/cl_core.hpp"
#include "OpenCL/Utility/cl_utility.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"
#include "OpenCL/Sampling/cl_xsadd_sampler.hpp"

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
template <>
UniquePointer<cl::Buffer> makeSamplerBuffer<zisc::XsaddEngin>(
    const QSettings& settings,  
    const ClCore& core,
    const std::size_t size)
{
  const auto key = QString{keyword::system_group} + "/" + keyword::random_seed;
  cl_uint seed = value<cl_uint>(settings, key);

  std::vector<ClXsaddState> sampler_list;
  sampler_list.reserve(size);
  for (std::size_t index = 0; index < size; ++index)
    sampler_list.emplace_back(seed + index);

  constexpr auto buffer_flag = CL_MEM_READ_WRITE | 
                               CL_MEM_HOST_NO_ACCESS | 
                               CL_MEM_COPY_HOST_PTR;
  const std::size_t memory = sizeof(ClXsaddState) * size;
  return makeBuffer("Sampler",
                    core.context(),
                    buffer_flag,
                    memory,
                    sampler_list.data());
}

/*!
  \details
  No detailed.
  */
template <>
std::string getSamplerOptions<zisc::XsaddEngin>()
{
  return std::string{" -D REFLECT_XSADD_SAMPLER"};
}

/*!
  \details
  No detailed.
  */
template <>
std::string getSamplerSource<zisc::XsaddEngin>()
{
  return std::string{"xsadd_sampler.cl"};
}

} // namespace reflect
