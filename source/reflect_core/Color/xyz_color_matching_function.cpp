/*!
  \file color_matching_function.cpp
  \author takemura
  */

#include "xyz_color_matching_function.hpp"
// Qt
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/arithmetic_array.hpp"
#include "zisc/error.hpp"
// Reflect
#include "keyword.hpp"
#include "reflect_config.hpp"
#include "spectral_distribution.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
XyzColorMatchingFunction::XyzColorMatchingFunction(const QString& standard_observer,
                                                   const QString& standard_illuminant)
{
  initialize(standard_observer, standard_illuminant);
}

/*!
  \details
  No detailed.
  */
void XyzColorMatchingFunction::initialize(const QString& standard_observer,
                                          const QString& standard_illuminant)
{
  setStandardObserver(standard_observer);
  setStandardIlluminant(standard_illuminant);
}

/*!
  \details
  No detailed.
  */
void XyzColorMatchingFunction::setStandardIlluminant(const QString& standard_illuminant)
{
  switch (zisc::toHash32(standard_illuminant.toStdString().c_str())) {
   case zisc::toHash32(keyword::cie_d65):
    standard_illuminant_ = makeSpectra(":/property/cie_si_d65.csv");
    break;
   case zisc::toHash32(keyword::cie_a):
    standard_illuminant_ = makeSpectra(":/property/cie_si_a.csv");
    break;
   default:
    zisc::raiseError("XyzColorMatchingFunctionError: Unsupported standard illuminant.");
    break;
  }
  standard_illuminant_ = standard_illuminant_.normalized();
}

/*!
  \details
  No detailed.
  */
void XyzColorMatchingFunction::setStandardObserver(const QString& standard_observer)
{
  switch (zisc::toHash32(standard_observer.toStdString().c_str())) {
   case zisc::toHash32(keyword::cie2_cmf):
     x_bar_ = makeSpectra(":/property/cie_sco_2degree_xbar.csv");
     y_bar_ = makeSpectra(":/property/cie_sco_2degree_ybar.csv");
     z_bar_ = makeSpectra(":/property/cie_sco_2degree_zbar.csv");
    break;
   case zisc::toHash32(keyword::cie10_cmf):
     x_bar_ = makeSpectra(":/property/cie_sco_10degree_xbar.csv");
     y_bar_ = makeSpectra(":/property/cie_sco_10degree_ybar.csv");
     z_bar_ = makeSpectra(":/property/cie_sco_10degree_zbar.csv");
    break;
   default:
    zisc::raiseError("XyzColorMatchingFunctionError: Unsupported standard observer.");
    break;
  }

//  constexpr double k = 107.0;
//  x_bar_ = x_bar_.normalized() * k;
//  y_bar_ = y_bar_.normalized() * k;
//  z_bar_ = z_bar_.normalized() * k;
}

} // namespace reflect
