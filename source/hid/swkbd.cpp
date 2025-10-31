#include "hid/swkbd.hpp"
#include "errors.hpp"

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

void Swkbd::setHint(const char *hint) { swkbdSetHintText(&kbd, hint); }

void Swkbd::setValidation(SwkbdValidInput input) {
    swkbdSetValidation(&kbd, input, 0, 0);
}

Result Swkbd::getInput(std::string &outText) {
    outText.resize(maxLen + 1);

    Result res = swkbdInputText(&kbd, outText.data(), outText.size());
    if (R_FAILED(res)) {
        outText.clear();
        return res;
    }
    outText.shrink_to_fit();
    return MAKERESULT(RL_SUCCESS, RS_SUCCESS, RM_APPLICATION, RD_SUCCESS);
}

} // namespace xs::hid
