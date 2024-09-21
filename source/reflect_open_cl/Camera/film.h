/*!
 \file film.h
 \author takemura
 */

#ifndef _REFLECT_FILM_H_
#define _REFLECT_FILM_H_

#include "sampler.h"

/*! \brief Sample film coordinate */
float2 sampleFilmCoordinate(const size_t pixel_index, SamplerState* sampler);

#endif /* _REFLECT_FILM_H_ */
