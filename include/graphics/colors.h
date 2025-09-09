/**
 * @file colors.h
 * @brief Common color constants for graphics (RGBA packed into u32).
 */
#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <string>

namespace xs::graphics {

	/**
	 * @brief Common color constants (RGBA packed into u32 using C2D_Color32).
	 */
	///@{
	extern const u32 clrWhite;
	extern const u32 clrBlack;
	extern const u32 clrRed;
	extern const u32 clrGreen;
	extern const u32 clrBlue;
	extern const u32 clrYellow;
	extern const u32 clrCyan;
	extern const u32 clrMagenta;
	///@}

}
