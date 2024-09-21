/*!
	\file		pseudo-color.hpp
	\author takemura
*/


#include <vector>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <tuple>

#pragma once

class PseudoColor{
	public:
		typedef std::tuple<unsigned char, unsigned char, unsigned char> rgbColor;
		PseudoColor();

		// get pseudo-color
		rgbColor getColor(const std::size_t index);

		// reverse pseudo-color
		void clearColor();

	private:
		std::vector<rgbColor> PCRGB;
};

inline PseudoColor::rgbColor getColor(const std::size_t index);
inline void clearColor();