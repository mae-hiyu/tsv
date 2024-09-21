/*!
  \file geometry.hpp
  \author takemura
  */

#ifndef _REFLECT_GEOMETRY_HPP_
#define _REFLECT_GEOMETRY_HPP_

// Standard C++ library
#include <cstddef>
#include <vector>
#include <utility>
// Reflect
#include "reflect_config.hpp"
#include "LinearAlgebra/vector.hpp"
#include "Sampling/sampled_point.hpp"
#include "Utility/unique_pointer.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
class Aabb;
class IntersectionInfo;
class Ray;
class Sampler;

//! \addtogroup Geometry
//! \{

/*!
  \details
  No detailed.
  */
class Geometry
{
 public:
  virtual ~Geometry() {}


  //! Return the bounding box
  virtual Aabb boundingBox() const = 0;

  //! Return the surface area of geometry
  double surfaceArea() const;

  //! Test ray-geometry intersection
  virtual bool isIntersected(const Ray& ray,
                             IntersectionInfo* intersection) const = 0;

  //! Print member variable data
  static std::size_t printMemberData();

  //! Sample point randomly on the surface of geometry
  virtual std::pair<SampledPoint, Vector3> samplePoint(Sampler& sampler) const = 0;

  //! Sample a point randomly on the surface of the geometry using importance sampling
  virtual std::pair<SampledPoint, Vector3> samplePoint(
      const IntersectionInfo& intersection,
      Sampler& sampler) const = 0;

  //! Set surface area of geometry
  void setSurfaceArea(const double surface_area);

  //! Apply affine transformation
  virtual void transform(const Matrix4x4& matrix) = 0;

 private:
  double surface_area_;
};

//! Make geometries
std::vector<UniquePointer<Geometry>> makeGeometry(const QSettings& settings,
                                                  const QString& prefix);

//! \} Geometry

} // namespace reflect

#include "geometry-inl.hpp"

#endif // _REFLECT_GEOMETRY_HPP_
