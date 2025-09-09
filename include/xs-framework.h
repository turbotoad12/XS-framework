#include <3ds.h>
// --- Graphics includes ---
#include "graphics/text.h"

// --- Filesystem includes ---
#include "fs/fs.h"

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