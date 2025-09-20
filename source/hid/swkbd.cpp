#include "hid/swkbd.h"


namespace xs::hid {

    Swkbd::Swkbd(int flags, size_t maxLen) {
        swkbdInit(&kbd, SWKBD_TYPE_NORMAL, 2, -1);
        swkbdSetHintText(&kbd, "Enter text");
        swkbdSetFeatures(&kbd, SWKBD_DEFAULT_QWERTY);

        this->maxLen = maxLen;

        if (flags & SWKBD_NUMERIC) {
            // numeric-only mode can be enabled via features if needed
        }
        if (flags & SWKBD_PASSWORD) {
            swkbdSetPasswordMode(&kbd, SWKBD_PASSWORD_HIDE_DELAY);
        }
    }

    void Swkbd::setHint(const char* hint) {
        swkbdSetHintText(&kbd, hint);
    }

    void Swkbd::setValidation(SwkbdValidInput input) {
        swkbdSetValidation(&kbd, input, 0, 0);
    }

    std::string Swkbd::getInput() {
        std::string out;
        out.resize(maxLen + 1);

        Result res = swkbdInputText(&kbd, out.data(), out.size());
        if (R_FAILED(res)) return "";
        out.shrink_to_fit();
        return out;
    }

} // namespace xs::hid



