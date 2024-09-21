/*!
  \file floating_point.hpp
  \author takemura
  */

#ifndef _REFLECT_FLOATING_POINT_HPP_
#define _REFLECT_FLOATING_POINT_HPP_

// Standard C++ library
#include <cstddef>
// Reflect
#include "reflect_config.hpp"

#ifdef REFLECT_FLOAT_CHECK
// Qt
#include <QDebug>
#endif // REFLECT_FLOAT_CHECK

namespace reflect {

// Forward declaration
template <std::size_t> class SampledSpectra;
class SpectralDistribution;

//! \addtogroup Utility  
//! \{

//! Check if the float value is not between 0 and 1
bool isBetweenZeroAndOneFloat(const double value);

//! Check if the sample contains the value that is not between 0 and 1
template <std::size_t kSampleSize>
bool isBetweenZeroAndOneFloat(const SampledSpectra<kSampleSize>& sample);

//! Check if the sample contains the value that is not between 0 and 1
bool isBetweenZeroAndOneFloat(const SpectralDistribution& distribution);

//! Check if the float value is inf
bool isInfFloat(const double value);

//! Check if the sample contains inf value
template <std::size_t kSampleSize>
bool isInfFloat(const SampledSpectra<kSampleSize>& sample);

//! Check if spectra data has inf value
bool isInfFloat(const SpectralDistribution& sample);

//! Check if the float value is nan
bool isNanFloat(const double value);

//! Check if the sample contains nan value
template <std::size_t kSampleSize>
bool isNanFloat(const SampledSpectra<kSampleSize>& sample);

//! Check if the spectra data has nan value
bool isNanFloat(const SpectralDistribution& property);

//! Check if the float value is negative
bool isNegativeFloat(const double value);

//! Check if the sample contains negative value
template <std::size_t kSampleSize>
bool isNegativeFloat(const SampledSpectra<kSampleSize>& sample);

//! Check if the float value is 0
bool isZeroFloat(const double value);

//! Check if the spectra data has zero value
bool isZeroFloat(const SpectralDistribution& property);

//! Check if the vector has zero value
bool isZeroFloat(const Vector3& vector);

//! Check if the vector is unit vector
bool isUnitVector(const Vector3& vector);

//!
void printFloatValue(const double value);

//!
template <std::size_t kSampleSize>
void printFloatValue(const SampledSpectra<kSampleSize>& /* sample */) {}

#ifdef REFLECT_FLOAT_CHECK

#define REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(value) \
    if (!isBetweenZeroAndOneFloat(value)) \
        qDebug() << __FILE__ ": " <<  __LINE__ \
                 << ": " #value " has value that is not between 0 and 1."; \
    if (!isBetweenZeroAndOneFloat(value)) \
        printFloatValue( value )

#define REFLECT_CHECK_INF_FLOAT(value) \
    if (isInfFloat(value)) \
        qDebug() << __FILE__ ": " << __LINE__ << ": " #value " has inf."

#define REFLECT_CHECK_NAN_FLOAT(value) \
    if (isNanFloat(value)) \
        qDebug() << __FILE__ ": " << __LINE__ << ": " #value " has nan."

#define REFLECT_CHECK_NON_ZERO_FLOAT(value) \
    if (isZeroFloat(value)) \
        qDebug() << __FILE__ ": " << __LINE__ << ": " #value " has zero."

#define REFLECT_CHECK_POSITIVE_FLOAT(value) \
    if (isNegativeFloat(value)) \
        qDebug() << __FILE__ ": " << __LINE__ << ": " #value " has negative."; \
    if (isNegativeFloat(value)) \
        printFloatValue( value )

#define REFLECT_CHECK_VALID_FLOAT(value) \
    if (isInfFloat(value)) \
        qDebug() << __FILE__ ": " << __LINE__ << ": " #value " has inf."; \
    if (isNanFloat(value)) \
        qDebug() << __FILE__ ": " << __LINE__ << ": " #value " has nan."

#define REFLECT_CHECK_UNIT_VECTOR(vector) \
    if (!isUnitVector(vector)) \
        qDebug() << __FILE__ ": " << __LINE__ << ": " #vector " is not unit."

#else // REFLECT_FLOAT_CHECK

#define REFLECT_CHECK_BETWEEN_ZERO_AND_ONE_FLOAT(value)

#define REFLECT_CHECK_INF_FLOAT(value)

#define REFLECT_CHECK_NAN_FLOAT(value)

#define REFLECT_CHECK_NON_ZERO_FLOAT(value)

#define REFLECT_CHECK_POSITIVE_FLOAT(value)

#define REFLECT_CHECK_VALID_FLOAT(value)

#define REFLECT_CHECK_UNIT_VECTOR(vector)

#endif // REFLECT_FLOAT_CHECK

//! \} Utility

} // namespace reflect

#include "floating_point-inl.hpp"

#endif // _REFLECT_FLOATING_POINT_HPP_
