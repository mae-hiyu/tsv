/*!
  \file sampled_point-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_POINT_INL_HPP_
#define _REFLECT_SAMPLED_POINT_INL_HPP_

#include "sampled_point.hpp"
// Reflect
#include "LinearAlgebra/point.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
SampledPoint::SampledPoint() :
    inverse_pdf_{1.0}
{
}

/*!
  \details
  No detailed.
  */
inline
SampledPoint::SampledPoint(const Point3& point, const double inverse_pdf) :
    point_{point},
    inverse_pdf_{inverse_pdf}
{
}

/*!
  \details
  No detailed.
  */
inline
double SampledPoint::inversePdf() const
{
  return inverse_pdf_;
}

/*!
  \details
  No detailed.
  */
inline
const Point3& SampledPoint::point() const
{
  return point_;
}

/*!
  \details
  No detailed.
  */
inline
double SampledPoint::pdf() const
{
  return 1.0 / inverse_pdf_;
}

/*!
  \details
  No detailed.
  */
inline
void SampledPoint::setInversePdf(const double inverse_pdf)
{
  inverse_pdf_ = inverse_pdf;
}

/*!
  \details
  No detailed.
  */
inline
void SampledPoint::setPoint(const Point3& point)
{
  point_ = point;
}

/*!
  \details
  No detailed.
  */
inline
void SampledPoint::setPdf(const double pdf)
{
  inverse_pdf_ = 1.0 / pdf;
}

} // namespace reflect

#endif // _REFLECT_SAMPLED_POINT_INL_HPP_
