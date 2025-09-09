/**
 * @file controls.h
 * @brief HID (Human Interface Device) related utilities.
 *
 */
#pragma once

#include <3ds.h>
#include <string>

namespace xs::hid::control {

	/**
	 * @brief Scan the current state of all input devices.
	 *
	 * Calls libctru's hidScanInput() to sample controllers. This should be
	 * called once per frame before querying key/button state.
	 */
	inline void ScanInput();

	/**
	 * @brief Returns keys that were pressed since the last scan.
	 *
	 * @return u32 Bitmask of keys pressed (use HID macros to decode).
	 */
	inline u32 GetKeysPressed();

	/**
	 * @brief Returns keys currently held down.
	 *
	 * @return u32 Bitmask of keys held.
	 */
	inline u32 GetKeysHeld();

	/**
	 * @brief Returns keys that were released since the last scan.
	 *
	 * @return u32 Bitmask of keys released.
	 */
	inline u32 GetKeysReleased();

	/**
	 * @brief Reads the current circle pad position.
	 *
	 * @return circlePosition Current circle pad position.
	 */
	inline circlePosition GetCirclePadPosition();

}