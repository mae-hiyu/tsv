/*!
  \file shader_model.hpp
  \author takemura
  */

#ifndef _REFLECT_SHADER_MODEL_HPP_
#define _REFLECT_SHADER_MODEL_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"
#include "Utility/unique_pointer.hpp"

namespace reflect {

// Forward declaration
class IntersectionInfo;
class SampledDirection;
template <std::size_t> class SampledSpectra;
class Sampler;
class SurfaceModel;
template <std::size_t> class WavelengthSamples;

//! \addtogroup Material
//! \{

/*!
  \details
  No detailed.
  */
enum class ShaderType : int
{
  Diffuse = 0,
  Specular,
  Glossy
};

/*!
 \brief Shader class
 \details
 No detailed.
  */
template <std::size_t kSampleSize>
class ShaderModel
{
 public:
  using Spectra = SampledSpectra<kSampleSize>;
  using Wavelengths = WavelengthSamples<kSampleSize>;


  //! Create a shader model
  ShaderModel();

  virtual ~ShaderModel() {}


  // Dummy delete function
  static void operator delete(void*) {}

  //! Dummy new function
  static void* operator new(std::size_t, void* memory) 
  {
    return memory;
  }


  //! Evaluate the weight (Fs(i, o, n) * cos(theta_o) / pdf) of solid angle sampling
  virtual Spectra evaluateWeight(const Vector3* vin,
                                 const SampledDirection* vout,
                                 const Wavelengths& wavelengths) const = 0;

  //! Evaluate the radiance of the area sampling
  virtual Spectra evaluateRadiance(const Vector3* vin, 
                                   const Vector3* vout,
                                   const Wavelengths& wavelengths) const = 0;

  //! Make a BxDF
  static UniquePointer<ShaderModel> makeBxdf(const SurfaceModel& surface,
                                             const Vector3* vin,
                                             const IntersectionInfo& intersection,
                                             const Wavelengths& wavelengths,
                                             Sampler& sampler,
                                             MemoryPool& memory_pool);

  //! Print member variable data
  static std::size_t printMemberData();

  //! Return the shader type
  virtual ShaderType type() const = 0;

  //! Sample a next direction
  virtual SampledDirection sampleDirection(Sampler& sampler) const = 0;

  //! Check if wavelength selection occured
  virtual bool wavelengthIsSelected() const = 0;
};

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class DiffuseShaderModel : public ShaderModel<kSampleSize>
{
 public:
  //! Return the diffuse type
  ShaderType type() const override
  {
    return ShaderType::Diffuse;
  }
};

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class SpecularShaderModel : public ShaderModel<kSampleSize>
{
 public:
  //! Return the specular type
  ShaderType type() const override
  {
    return ShaderType::Specular;
  }
};

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize>
class GlossyShaderModel : public ShaderModel<kSampleSize>
{
 public:
  //! Return the glossy type
  ShaderType type() const override
  {
    return ShaderType::Glossy;
  }
};

//! \} Material

} // namespace reflect

#include "shader_model-inl.hpp"

#endif // _REFLECT_SHADER_MODEL_HPP_
