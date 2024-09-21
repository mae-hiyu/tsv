/*!
  \file camera_model.cpp
  \author takemura
  */

#include "camera_model.hpp"
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
// Reflect
#include "keyword.hpp"
#include "pinhole_camera.hpp"
//#include "thin_lens_camera_model.hpp"
#include "Utility/size.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

// Forward declaration
class Film;
class ColorSystem;

/*!
  \details
  No detailed.
  */
CameraModel::CameraModel(const ColorSystem& color_system,
                         const QSettings& settings, 
                         const QString& prefix) :
    jittering_{0.0, 0.0}
{
  initialize(color_system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
void CameraModel::initialize(const ColorSystem& /* color_system */,
                             const QSettings& /* settings */, 
                             const QString& /* prefix */)
{
}

/*!
  \details
  No detailed.
  */
std::size_t CameraModel::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(normal_);
  size += PRINT_VARIABLE_DATA(sampled_lens_point_);
  size += PRINT_VARIABLE_DATA(jittering_);
  size += PRINT_VARIABLE_DATA(film_);
  return size;
}

/*!
  \details
  No detailed.
  */
UniquePointer<CameraModel> makeCameraModel(const ColorSystem& color_system,
                                           const QSettings& settings, 
                                           const QString& prefix)
{
  CameraModel* camera_model = nullptr;

  const auto camera_model_type = 
      value<QString>(settings, prefix + "/" + keyword::camera_model);
  switch (zisc::toHash32(camera_model_type.toStdString().c_str())) {
   case zisc::toHash32(keyword::pinhole_camera):
    camera_model = new PinholeCamera{color_system, settings, prefix};
    break;
//   case zisc::toHash32(keyword::thin_lens_camera_model):
//    camera_model = new ThinLensCameraModel{color_system, settings, prefix, film};
//    break;
   default:
    zisc::raiseError("CameraModelError: Unsupported type is specified.");
    break;
  }
  return UniquePointer<CameraModel>{camera_model};
}

} // namespace reflect
