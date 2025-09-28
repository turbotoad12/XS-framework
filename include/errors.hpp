// xs_errors.h
#pragma once
#include <3ds.h>
#include <string>

namespace xs::errors {

    // Decode a Result into a readable string
    inline std::string decode(Result res) {
        int desc = R_DESCRIPTION(res);
        int mod  = R_MODULE(res);
        int sum  = R_SUMMARY(res);
        int lvl  = R_LEVEL(res);

        char buf[256];
        snprintf(buf, sizeof(buf),
                 "Result: 0x%08lX\n"
                 " Level: %d\n"
                 " Summary: %d\n"
                 " Module: %d\n"
                 " Description: %d",
                 res, lvl, sum, mod, desc);
        return std::string(buf);
    }

    // Show error with applet using decoded message
    inline void show(Result res, bool softwareReset = false, bool homeButton = true) {
        errorConf err;
        errorInit(&err, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
        err.softwareReset = softwareReset;
        err.homeButton = homeButton;
        std::string msg = decode(res);
        errorText(&err, msg.c_str());
        errorDisp(&err);
    }

    // Show custom error text directly
    inline void show(const char* msg) {
        errorConf err;
        errorInit(&err, ERROR_TEXT_WORD_WRAP, CFG_LANGUAGE_EN);
        errorText(&err, msg);
        errorDisp(&err);
    }

} // namespace xs::errors
