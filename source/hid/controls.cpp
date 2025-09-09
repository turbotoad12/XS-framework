#include "hid/controls.h"

namespace xs::hid::control {
    /**
     * @brief Scans the current state of all input devices.
     */
    inline void ScanInput() {
        hidScanInput();
    }

    /**
     * @brief Gets the keys that were just pressed.
     */
    inline u32 GetKeysPressed() {
        return hidKeysDown();
    }

    /**
     * @brief Gets the keys that are currently being held.
     */
    inline u32 GetKeysHeld() {
        return hidKeysHeld();
    }

    /**
     * @brief Gets the keys that were just released.
     */
    inline u32 GetKeysReleased() {
        return hidKeysUp();
    }

    /**
     * @brief Gets the current position of the circle pad.
     * @return circlePosition Current circle pad position.
     */
    inline circlePosition GetCirclePadPosition() {
        circlePosition pos;
        hidCircleRead(&pos);
        return pos;
    }

}