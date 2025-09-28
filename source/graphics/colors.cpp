#include "graphics/colors.hpp"



namespace xs::graphics {
    // Define color constants
    const u32 clrWhite = C2D_Color32(255, 255, 255, 255);
    const u32 clrBlack = C2D_Color32(0, 0, 0, 255);
    const u32 clrRed = C2D_Color32(255, 0, 0, 255);
    const u32 clrGreen = C2D_Color32(0, 255, 0, 255);
    const u32 clrBlue = C2D_Color32(0, 0, 255, 255);
    const u32 clrYellow = C2D_Color32(255, 255, 0, 255);
    const u32 clrCyan = C2D_Color32(0, 255, 255, 255);
    const u32 clrMagenta = C2D_Color32(255, 0, 255, 255);
    const u32 clrClear = C2D_Color32(0, 0, 0, 0);


    /**
     * @brief Convert a hex color string to a u32 color value.
     * @param hexStr The hex color string (e.g., "#RRGGBB" or "RRGGBB").
     * @param alpha Value from 0-255 (Transparency)
     * @return u32 (or C2D_Color32)
     */
    u32 color(const std::string& hexStr, int alpha) {
        // Convert hex string (e.g., "#RRGGBB" or "RRGGBB") to u32 color
        std::string str = hexStr;
        if (str[0] == '#') {
            str = str.substr(1);
        }
        if (str.length() != 6) {
            return clrMagenta; // Default to magenta on error
        }
        u8 r = static_cast<u8>(std::stoi(str.substr(0, 2), nullptr, 16));
        u8 g = static_cast<u8>(std::stoi(str.substr(2, 2), nullptr, 16));
        u8 b = static_cast<u8>(std::stoi(str.substr(4, 2), nullptr, 16));
        // if theres an error display clrMagenta
        if (r == 0 && g == 0 && b == 0 && str != "000000") {
            return clrMagenta;
        }
        if (alpha < 0) alpha = 0;
        if (alpha > 255) alpha = 255;
        return C2D_Color32(r, g, b, alpha);
    }
}