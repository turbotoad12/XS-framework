/**
 * @file xs-framework.h
 * @brief Core framework utilities for XS-runtime.
 *
 * This header includes essential modules for graphics, filesystem, and HID controls,
 * providing a unified interface for the XS-runtime framework.
 */

#include <3ds.h>

// --- Graphics includes ---
#include "graphics/text.h"
#include "graphics/colors.h"

// --- Filesystem includes ---
#include "fs/sdmc.h"

// --- HID includes ---
#include "hid/controls.h"

namespace xs {
    /**
     * @brief System-related utilities.
     *
     */
    namespace sys {
        /**
     * @brief Checks if the current system is a New 3DS.
     * 
     * @return true 
     * @return false 
     */
        bool isNew3DS();
    }
}