/*!
 \file reflect_config.hpp
 \author takemura
 */

#ifndef _REFLECT_CONFIG_HPP_
#define _REFLECT_CONFIG_HPP_

// Standard C++ library
#include <cstddef>
#include <string>
#include <type_traits>
#include <vector>
// Qt
#include <QHash>
#include <QString>
#include <QVariant>
// Zisc
#include "zisc/arithmetic_array.hpp"
// Reflect
#include "zisc/xsadd_engin.hpp"

// Forward declaration
namespace zisc {
template <typename,std::size_t> class Point;
template <typename,std::size_t> class Vector;
template <typename,std::size_t,std::size_t> class Matrix;
template <std::size_t, std::size_t> class AlignedMemoryPool;
} // namespace zisc

//! \addtogroup Renderer
//! \{

constexpr char kReflectName[] = "TSVRenderer";
constexpr std::size_t kReflectVersionMajor = 0;
constexpr std::size_t kReflectVersionMinor = 1;
constexpr std::size_t kReflectVersionPatch = 0;
constexpr char kReflectVersion[] = "0.1.0";

//! \} Renderer 

namespace reflect {

//! \addtogroup Renderer
//! \{

using ReflectTable = QHash<QString, QVariant>;
using ReflectSamplerType = zisc::XsaddEngin;
constexpr std::size_t kMemoryPoolSize = 32768;
constexpr std::size_t kMemoryAlignment = std::alignment_of<void*>::value;
using MemoryPool = zisc::AlignedMemoryPool<kMemoryPoolSize, kMemoryAlignment>;

//! \}

//! \addtogroup Color 
//! \{

constexpr std::size_t kShortestWavelength = 380;
constexpr std::size_t kLongestWavelength = 780;

static_assert(kShortestWavelength >= 300, 
              "## The shortest wavelength must be greater than equal to 300nm.");
static_assert(kLongestWavelength <= 830, 
              "## The longest wavelength must be less than equal to 830nm.");
static_assert(kShortestWavelength < kLongestWavelength,
              "## The shortest wavelength must be less than to the longest.");

constexpr std::size_t kWavelengthRange = kLongestWavelength - kShortestWavelength;
constexpr std::size_t kWavelengthResolution = 1;

static_assert(kWavelengthRange % kWavelengthResolution == 0,
              "## Invalid wavelength resolution.");

constexpr std::size_t kSpectraSize = kWavelengthRange / kWavelengthResolution;
constexpr std::size_t kBlueWavelength = 440;
constexpr std::size_t kGreenWavelength = 540;
constexpr std::size_t kRedWavelength = 700;

// For TSV Rendering
constexpr std::size_t kXYZSampleSize = 2;
constexpr std::size_t kLightSampleSize = 6;

static_assert((kBlueWavelength - kShortestWavelength) % kWavelengthResolution == 0,
              "## Invalid wavelength resolution.");
static_assert((kGreenWavelength - kShortestWavelength) % kWavelengthResolution == 0,
              "## Invalid wavelength resolution.");
static_assert((kRedWavelength - kShortestWavelength) % kWavelengthResolution == 0,
              "## Invalid wavelength resolution.");

//! \} Color

//! \addtogroup DataStructure
//! \{

constexpr std::size_t kMaxNodeObjects = 4;

//! \}

//! \addtogroup Geometry
//! \{

enum class GeometryType : int
{
  kPlane = 0,
  kSphere,
  kFlatMesh
};

//! \}

//! \addtogroup LinearAlgebra
//! \{

using Vector3 = zisc::Vector<double, 3>;
using Vector2 = zisc::Vector<double, 2>;
using Point3 = zisc::Point<double, 3>;
using Point2 = zisc::Point<double, 2>;
using Matrix4x4 = zisc::Matrix<double, 4, 4>;
using Matrix3x3 = zisc::Matrix<double, 3, 3>;

//! \} LinearAlgebra

//! \addtogroup Sampling
//! \{

constexpr std::size_t kWavelengthSampleSize = 400;

template <std::size_t kSampleSize>
using IntensitySamples = zisc::ArithmeticArray<double, kSampleSize>;

//! \} Sampling

} // namespace reflect

#endif // _REFLECT_CONFIG_HPP_
