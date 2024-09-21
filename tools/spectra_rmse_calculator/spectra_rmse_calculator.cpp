/*!
  \file spectra_rmse_calculator.cpp
  \author zin
  */

// Standard C++ library
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <functional>
#include <future>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
// Qt
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QFileInfo>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QString>
// Zisc
#include "zisc/binary_file.hpp"
#include "zisc/thread_pool.hpp"

class SpectraImage
{
 public:
  using FloatType = float;


  //! Make a spectra image
  SpectraImage(const QString& file_path)
  {
    initialize(file_path);
  }

  //! Return the pixel data
  const std::vector<FloatType>& data() const
  {
    return data_;
  }

  //! Return the image height resolution
  std::size_t height() const
  {
    return height_;
  }

  //! Return the spectra size per pixel
  std::size_t spectraSize() const
  {
    return spectra_size_;
  }

  //! Return the image width resolution
  std::size_t width() const
  {
    return width_;
  }

 private:
  //! Initialize
  void initialize(const QString& file_path)
  {
    zisc::ReadBinary spectra_data;
    spectra_data.open(file_path.toStdString());

    // Image resolution
    width_ = spectra_data.read<std::uint32_t>();
    height_ = spectra_data.read<std::uint32_t>();
    // Spectra information
    lambda_min_ = spectra_data.read<std::uint16_t>();
    delta_lambda_ = spectra_data.read<std::uint16_t>();
    spectra_size_ = spectra_data.read<std::uint16_t>();
    // Float type
    float_type_ = spectra_data.read<std::uint8_t>();
    // Image data
    switch (float_type_) {
     case 0:
      loadSpectraData<float>(spectra_data);
      break;
     default:
      std::cerr << "## Unsupported floating point type." << std::endl;
      break;
    }
  }

  //! Load spectra data
  template <typename Float>
  void loadSpectraData(zisc::ReadBinary& spectra_data)
  {
    const std::size_t size = width_ * height_ * spectra_size_;
    data_.resize(size, 0.0f);
    for (std::size_t i = 0; i < size; ++i)
      data_[i] = static_cast<FloatType>(spectra_data.read<Float>());
  }

  std::size_t width_,
              height_;
  std::size_t lambda_min_,
              delta_lambda_,
              spectra_size_;
  std::size_t float_type_;
  std::vector<FloatType> data_;
};

//! Calculate RMS error
double calculateRmsError(const SpectraImage& image1, const SpectraImage& image2)
{
  //! \todo Check image size and spectra size

  const auto& data1 = image1.data();
  const auto& data2 = image2.data();
  const std::size_t size = data1.size();
  double square_error_sum = 0.0;
  for (std::size_t i = 0; i < size; ++i) {
    const double error = static_cast<double>(data1[i] - data2[i]);
    square_error_sum += error * error;
  }
  return std::sqrt(square_error_sum / static_cast<double>(size));
}

int main(int argc, char** argv)
{
  QCoreApplication application{argc, argv};
  QCoreApplication::setApplicationName("SpectraRmseCalculator");
  QCoreApplication::setApplicationVersion("0.1");

  QCommandLineParser parser;
  parser.addHelpOption();
  parser.addVersionOption();
  parser.setApplicationDescription("Calculate RMS error between reference and images.");
  parser.addPositionalArgument("reference", "Reference spectra image.");
  parser.addPositionalArgument("images", "Spectra images.");

  parser.process(application);

  const auto image_list = parser.positionalArguments();
  if (image_list.size() < 2)
    parser.showHelp();

  // Refelence image
  const SpectraImage reference_image{image_list[0]};

  zisc::ThreadPool thread_pool;
  std::vector<std::future<std::pair<QString, double>>> result_list;
  result_list.resize(image_list.size() - 1);
  QRegularExpression pass_regex{"(\\d+).*"};
  for (std::size_t i = 0; i < static_cast<std::size_t>(image_list.size() - 1); ++i) {
    const auto& image_path = image_list[i + 1];
    std::function<std::pair<QString, double> ()> calculate_rms_error{
    [&reference_image, &image_path, &pass_regex]()
    {
      // Get pass
      const QFileInfo info{image_path};
      const auto file_name = info.fileName();
      const auto match = pass_regex.match(file_name);
      const auto pass = match.captured(1);
      // Calculate rms error
      const SpectraImage image{image_path};
      const double rms_error = calculateRmsError(reference_image, image);
      return std::make_pair(pass, rms_error);
    }};
    result_list[i] = thread_pool.enqueue(std::move(calculate_rms_error));
  }

  std::vector<std::pair<QString, double>> rms_error_list;
  rms_error_list.resize(image_list.size() - 1);
  for (std::size_t i = 0; i < rms_error_list.size(); ++i)
    rms_error_list[i] = result_list[i].get();

  auto compare = [](const std::pair<QString, double>& a,
                    const std::pair<QString, double>& b)
  {
    return a.first.toInt() < b.first.toInt();
  };
  std::sort(rms_error_list.begin(), rms_error_list.end(), compare);

  std::ofstream output;
  output.open("rms_error.csv");
  output << "Pass, RMS error" << std::endl;
  for (const auto& value : rms_error_list)
    output << value.first.toStdString() << ", " << value.second << std::endl;

  return 0;
}
