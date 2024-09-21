/*!
  \file sampled_wavelengths.cpp
  \author takemura
  */

#include "sampled_wavelengths.hpp"
// Standard C++ library
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <tuple>
#include <iostream>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/math.hpp"
// Reflect
#include "reflect_config.hpp"
#include "world.hpp"
#include "Color/spectral_distribution.hpp"
#include "Data/object.hpp"
#include "Material/material.hpp"
#include "Material/EmitterModel/emitter_model.hpp"
#include "Material/SurfaceModel/surface_model.hpp"
#include <iostream>

namespace reflect {

using zisc::cast;

/*!
  \details
  No detailed.
  */
SpectralDistribution calculateLightPdf(const World& world)
{
  constexpr std::size_t exponent = 1; // Balance heuristics
//  constexpr std::size_t exponent = 2; // Power heuristics

  const auto& light_source_list = world.lightSourceList();

  double sum = 0.0;
  for (const auto& light_source : light_source_list) {
    auto object = light_source.object();
    const double p = object->geometry().surfaceArea() *
                     object->material().emitter().radiantEmittance();
    sum += zisc::power<exponent>(p);
  }

  const double inverse_sum = 1.0 / sum;
  SpectralDistribution pdf;
  for (const auto& light_source : light_source_list) {
    auto object = light_source.object();
    const auto& emitter = object->material().emitter();
    const double k = 1.0 / emitter.radiantEmittance();
    const double p = object->geometry().surfaceArea() * emitter.radiantEmittance();
    const double weight = zisc::power<exponent>(p) * inverse_sum;
    pdf += emitter.powerDistribution() * (k * weight);
  }
  return pdf.normalized();
}

/*!
  \details
  No detailed
  */
SpectralDistribution calculateReflectancePdf(const World& world)
{
  constexpr std::size_t exponent = 1; // Balance heuristics
 // constexpr std::size_t exponent = 2; // Power heuristics

  auto surface_list = world.surfaceList();
  std::sort(surface_list.begin(), surface_list.end());

  std::vector<std::tuple<SpectralDistribution, double, double>> surface_data;
  surface_data.reserve(surface_list.size());

  // MultiLayerThinFilms description
  // const auto pdf_0 = makeSpectra
  // ("/Users/takemura/Programs/TristimulusValuesRenderer/properties/reflectance/ThinFilm_Reflectance/SiO2-Cu/SiO2-Cu_0.csv").normalized();
  // const auto pdf_45 = makeSpectra
  // ("/Users/takemura/Programs/TristimulusValuesRenderer/properties/reflectance/ThinFilm_Reflectance/SiO2-Cu/SiO2-Cu_45.csv").normalized();

  // auto usePDF = pdf_0;

  // Set reflectance and distribution area 
  for (auto surface : surface_list) {
    surface_data.emplace_back(surface->reflectance(), 0.0, 0.0);
    auto& data = surface_data.back();
    std::get<2>(data) = std::get<0>(data).sum();
  }

  // Set geometry area
  const auto& object_list = world.objectList();
  for (const auto& object : object_list) {
    const auto& surface = object.material().surface();
    const std::size_t index = zisc::getIndex(surface_list.cbegin(), 
                                             surface_list.cend(), 
                                             &surface);
    const double area = object.geometry().surfaceArea();
    std::get<1>(surface_data[index]) += area;
  }

  double sum = 0.0;
  for (const auto& data : surface_data) {
    const double p = std::get<1>(data) * std::get<2>(data);
      sum += zisc::power<exponent>(p);
  }

  const double inverse_sum = 1.0 / sum;
  SpectralDistribution pdf;
  for (const auto& data : surface_data) {
    const double k = 1.0 / std::get<2>(data);
    const double p = std::get<1>(data) * std::get<2>(data);
    const double weight = zisc::power<exponent>(p) * inverse_sum;

    pdf += std::get<0>(data) * (k * weight);
  }
  return pdf.normalized();
}



} // namespace reflect
