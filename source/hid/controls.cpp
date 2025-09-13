#include "hid/controls.h"

namespace xs::hid::control {
    /**
     * @brief Gets the current position of the circle pad.
     * @return circlePosition Current circle pad position.
     */
    circlePosition GetCirclePadPosition() {
        circlePosition pos;
        hidCircleRead(&pos);
        return pos;
    }

}