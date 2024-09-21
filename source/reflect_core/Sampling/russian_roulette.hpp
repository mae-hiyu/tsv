/*!
  \file russian_roulette.hpp
  \author takemura
  */

#ifndef _REFLECT_RUSSIAN_ROULETTE_HPP_
#define _REFLECT_RUSSIAN_ROULETTE_HPP_

// Standard C++ library
#include <cstddef>
#include <functional>
// Zisc
#include "zisc/algorithm.hpp"

// Forward declaration
class QSettings;
class QString;

namespace reflect {

// Forward declaration
template <std::size_t> class SampledSpectra;
class Sampler;

//! \addtogroup Sampling
//! \{

/*!
  \details
  No detailed.
  */
class RouletteResult
{
 public:
  //! Create result
  RouletteResult();

  //! Create result
  RouletteResult(const bool result, const double probability);


  //! Return the probability
  double probability() const;

  //! Return the result
  bool result() const;

  //! Set probability
  void setProbability(const double probability);

  //! Set result
  void setResult(const bool result);

 private:
  double probability_;
  bool result_;
};

//! Play russian roulette
template <std::size_t kSampleSize>
RouletteResult playRussianRouletteWithAverage(
    const std::size_t path,
    const SampledSpectra<kSampleSize>& weight,
    Sampler& sampler);

//! Play russian roulette
template <std::size_t kSampleSize>
RouletteResult playRussianRouletteWithMax(
    const std::size_t path,
    const SampledSpectra<kSampleSize>& weight,
    Sampler& sampler);

//! Play russian roulette
template <std::size_t kSampleSize>
RouletteResult playRussianRouletteWithPath(
    const std::size_t max_path,
    const std::size_t path,
    const SampledSpectra<kSampleSize>& weight,
    Sampler& sampler);

template <std::size_t kSampleSize>
using RussianRouletteFunction = 
    std::function<RouletteResult (const std::size_t,
                                  const SampledSpectra<kSampleSize>&,
                                  Sampler&)>;

//! Make a russian roulette function
template <std::size_t kSampleSize>
RussianRouletteFunction<kSampleSize> makeRussianRoulette(const QSettings& settings,
                                                         const QString& prefix);

//! \} Sampling

} // namespace reflect

#include "russian_roulette-inl.hpp"

#endif // _REFLECT_RUSSIAN_ROULETTE_HPP_
