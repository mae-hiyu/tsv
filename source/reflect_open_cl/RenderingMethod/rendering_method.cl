/*!
 \file rendering_method.cl
 \author takemura
 */

#include "reflect_config.h"
#include "rendering_method.h"

/*!
 \details
 No detailed.
 */
bool getPixelIndex(global uint* number, uint* index)
{
  const uint n = atomic_inc(number);
  *index = n + kDevicePixelSize * get_global_offset(0);
  return n < kDevicePixelSize;
}
