/*!
  \file russian_roulette-inl.hpp
  \author takemura
  */

#ifndef _REFLECT_RUSSIAN_ROULETTE_INL_HPP_
#define _REFLECT_RUSSIAN_ROULETTE_INL_HPP_

#include "russian_roulette.hpp"
// Standard C++ library
#include <cstddef>
#include <functional>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
// Reflect
#include "keyword.hpp"
#include "Sampling/sampled_spectra.hpp"
#include "Sampling/sampler.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
inline
RouletteResult::RouletteResult() :
    probability_{1.0},
    result_{true}
{
}

/*!
  \details
  No detailed.
  */
inline
RouletteResult::RouletteResult(const bool result, const double probability) :
    probability_{probability},
    result_{result}
{
}

/*!
  \details
  No detailed.
  */
inline
double RouletteResult::probability() const
{
  return probability_;
}

/*!
  \details
  No detailed.
  */
inline
bool RouletteResult::result() const
{
  return result_;
}

/*!
  \details
  No detailed.
  */
inline
void RouletteResult::setProbability(const double probability)
{
  probability_ = probability;
}

/*!
  \details
  No detailed.
  */
inline
void RouletteResult::setResult(const bool result)
{
  result_ = result;
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
RouletteResult playRussianRouletteWithAverage(
    const std::size_t /* path */,
    const SampledSpectra<kSampleSize>& weight,
    Sampler& sampler)
{
  const double average = weight.average();
  const double probability = (average > 1.0) ? 1.0 : average;
  const bool result = sampler.sample(0.0, 1.0) < probability;
  return RouletteResult{result, result ? probability : 1.0 - probability};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
RouletteResult playRussianRouletteWithMax(
    const std::size_t /* path */,
    const SampledSpectra<kSampleSize>& weight,
    Sampler& sampler) 
{
  const double max = weight.max();
  const double probability = (max > 1.0) ? 1.0 : max;
  const bool result = sampler.sample(0.0, 1.0) < probability;
  return RouletteResult{result, result ? probability : 1.0 - probability};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
RouletteResult playRussianRouletteWithPath(
    const std::size_t max_path,
    const std::size_t path,
    const SampledSpectra<kSampleSize>& /* weight */,
    Sampler& /* sampler */)
{
  return RouletteResult{path < max_path, 1.0};
}

/*!
  \details
  No detailed.
  */
template <std::size_t kSampleSize> inline
RussianRouletteFunction<kSampleSize> makeRussianRoulette(const QSettings& settings,
                                                         const QString& prefix)
{
  RussianRouletteFunction<kSampleSize> russian_roulette;

  const auto type = value<QString>(settings, prefix + "/" + keyword::type);
  const auto type_hash = zisc::toHash32(type.toStdString().c_str());
  if (type_hash == zisc::toHash32(keyword::path_length)) {
    const auto max_length = 
        value<std::size_t>(settings, prefix + "/" + keyword::path_length_max);
    russian_roulette = std::bind(playRussianRouletteWithPath<kSampleSize>,
                                 max_length,
                                 std::placeholders::_1,
                                 std::placeholders::_2,
                                 std::placeholders::_3);
  }
  else if (type_hash == zisc::toHash32(keyword::reflectance_average)) {
    russian_roulette = playRussianRouletteWithAverage<kSampleSize>;
  }
  else if (type_hash == zisc::toHash32(keyword::reflectance_max)) {
    russian_roulette = playRussianRouletteWithMax<kSampleSize>;
  }
  else {
    zisc::raiseError("RussianRouletteError: Unsupported type is supecified.");
  }

  return russian_roulette;
}

} // namespace reflect

#endif // _REFLECT_RUSSIAN_ROULETTE_INL_HPP_
