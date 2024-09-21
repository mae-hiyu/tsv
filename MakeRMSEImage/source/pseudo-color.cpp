/*!
	\file		pseudo-color.cpp
	\author takemura
*/
#include "pseudo-color.hpp"


#include <iostream>

PseudoColor::PseudoColor()
{
	PCRGB.reserve(256);
	unsigned char r, g, b;
	for (std::size_t i = 0; i < 256; ++i)
	{
		if (i < 64)
		{
			r = 0;
			g = i * 255.0 / 63;
			b = 255;
		}
		else if (i < 128)
		{
			r = 0;
			g = 255;
			b = (127 - i) * (255.0 / 64.0);
		}
		else if (i < 192)
		{
			r = (i -127) * (255.0 / 64);
			g = 255;
			b = 0;

		}
		else{
			r = 255;
			g = (255 - i) * (255.0 / 64);
			b = 0;
		}
	PCRGB.emplace_back(r, g, b);
	}
}

PseudoColor::rgbColor PseudoColor::getColor(const std::size_t index)
{
	return PCRGB[index];
}

void PseudoColor::clearColor()
{
	PCRGB.clear();
}