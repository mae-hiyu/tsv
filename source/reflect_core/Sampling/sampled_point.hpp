/*!
  \file sampled_point.hpp
  \author takemura
  */

#ifndef _REFLECT_SAMPLED_POINT_HPP_
#define _REFLECT_SAMPLED_POINT_HPP_

// Reflect
#include "LinearAlgebra/point.hpp"

namespace reflect {

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
class SampledPoint
{
 public:
  //! Create sample
  SampledPoint();

  //! Create sample
  SampledPoint(const Point3& point, const double inverse_pdf);


  //! Return the inverse pdf
  double inversePdf() const;

  //! Return the sampled point
  const Point3& point() const;

  //! Return the pdf (probability density function) of the sampled point
  double pdf() const;

  //! Set inverse pdf
  void setInversePdf(const double inverse_pdf);

  //! Set point
  void setPoint(const Point3& point);

  //! Set pdf
  void setPdf(const double pdf);

 private:
  Point3 point_;
  double inverse_pdf_;
};

//! \} Sampling

} // namespace reflect

#include "sampled_point-inl.hpp"

#endif // _REFLECT_SAMPLED_POINT_HPP_
