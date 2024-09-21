/*!
  \file geometry.cpp
  \author takemura
  */

#include "geometry.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
#include <utility>
// Qt
#include <QSettings>
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
// Reflect
#include "keyword.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "triangle_mesh.hpp"
#include "Utility/size.hpp"
#include "Utility/unique_pointer.hpp"
#include "Utility/value.hpp"

namespace reflect {

/*!
  \details
  No detailed.
  */
void Geometry::setSurfaceArea(const double surface_area)
{
  surface_area_ = surface_area;
}

/*!
  \details
  No detailed.
  */
std::vector<UniquePointer<Geometry>> makeGeometry(const QSettings& settings,
                                                  const QString& prefix)
{
  std::vector<UniquePointer<Geometry>> geometry_list;

  const auto type = value<QString>(settings, prefix + "/" + keyword::geometry_type);
  switch (zisc::toHash32(type.toStdString().c_str())) {
   case zisc::toHash32(keyword::plane_type):
    geometry_list.emplace_back(new Plane{});
    break;
   case zisc::toHash32(keyword::sphere_type):
    geometry_list.emplace_back(new Sphere{});
    break;
   case zisc::toHash32(keyword::polygon_type):
    geometry_list = makeTriangles(
        value<QString>(settings, prefix + "/" + keyword::object_file),
        value<bool>(settings, prefix + "/" + keyword::enable_smoothing),
        value<bool>(settings, prefix + "/" + keyword::use_nagata_patch));
    break;
   default:
    zisc::raiseError("GeometryError: Unsupported type is specified.");
  }
  return std::move(geometry_list);
}

/*!
  \details
  No detailed.
  */
std::size_t Geometry::printMemberData()
{
  std::size_t size = 0;
  size += PRINT_VARIABLE_DATA(surface_area_);
  return size;
}

} // namespace reflect
