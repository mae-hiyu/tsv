/*!
  \file material_item_type.hpp
  \author takemura
  */

#ifndef _REFLECT_MATERIAL_ITEM_TYPE_HPP_
#define _REFLECT_MATERIAL_ITEM_TYPE_HPP_

namespace reflect {

/*!
  \details
  No detailed.
  */
enum class MaterialItemType : int
{
  SurfaceModel = 0,
  EmitterModel,
  Texture
};

} // namespace reflect

#endif // _REFLECT_MATERIAL_ITEM_TYPE_HPP_
