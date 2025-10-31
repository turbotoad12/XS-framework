#include "text.hpp"

namespace xs::text {

// Font implementation
Font::Font(const std::string &fontpath) {
    // Try to load the font directly first
    fontData = C2D_FontLoad(fontpath.c_str());

    // If loading failed and the path looks like a romfs path, try initializing romfs
    // and loading again. This helps when callers construct Font before romfsInit()
    // has been called elsewhere.
    if (!fontData && fontpath.rfind("romfs:/", 0) == 0) {
        Result rc = romfsInit();
        if (R_SUCCEEDED(rc)) {
            // Try loading again after romfs is available
            fontData = C2D_FontLoad(fontpath.c_str());
            if (!fontData) {
                printf("xs::text::Font: failed to load font '%s' even after romfsInit()\n", fontpath.c_str());
                loadResult = MAKERESULT(RL_PERMANENT, RS_NOTFOUND, RM_ROMFS, RD_NOT_FOUND);
            } else {
                loadResult = MAKERESULT(RL_SUCCESS, RS_SUCCESS, RM_ROMFS, RD_SUCCESS);
            }
            // Note: we don't call romfsExit() here because ownership of romfs lifecycle
            // should remain with the application. callers that called romfsInit()
            // should call romfsExit() when appropriate.
        } else {
            printf("xs::text::Font: romfsInit() failed with 0x%08X\n", rc);
            loadResult = rc;
        }
    } else if (!fontData) {
        // Font loading failed without romfs path
        loadResult = MAKERESULT(RL_PERMANENT, RS_NOTFOUND, RM_APPLICATION, RD_NOT_FOUND);
    } else {
        // Font loaded successfully
        loadResult = MAKERESULT(RL_SUCCESS, RS_SUCCESS, RM_APPLICATION, RD_SUCCESS);
    }
}

Font::~Font() {
    if (fontData) {
        C2D_FontFree(fontData);
        fontData = nullptr;
    }
}

void Font::Free() {
    if (fontData) {
        C2D_FontFree(fontData);
        fontData = nullptr;
    }
}

C2D_Font Font::GetHandle() const {
    return fontData;
}

bool Font::IsLoaded() const {
    return (fontData != nullptr);
}

Result Font::GetLoadResult() const {
    return loadResult;
}

// Text implementation
Text::Text(const std::string &content, Font *font)
    : content(content), font(font), staticBuf(nullptr) {
    staticBuf = C2D_TextBufNew(4096); // Supports up to 4096 glyphs
    if (staticBuf) {
        // If a custom font was provided and it is loaded, use it. Otherwise
        // fall back to the system font parsing to avoid crashes when the font
        // handle is null.
        if (font && font->IsLoaded()) {
            C2D_TextFontParse(&textData, font->GetHandle(), staticBuf, content.c_str());
        } else {
            C2D_TextParse(&textData, staticBuf, content.c_str());
        }
        C2D_TextOptimize(&textData);
    }
}

Text::Text(const std::string &content)
    : content(content), font(nullptr), staticBuf(nullptr) {
    staticBuf = C2D_TextBufNew(4096);
    if (staticBuf) {
        C2D_TextParse(&textData, staticBuf, content.c_str());
        C2D_TextOptimize(&textData);
    }
}

Text::~Text() {
    if (staticBuf) {
        C2D_TextBufDelete(staticBuf);
    }
}

void Text::Draw(float x, float y, float z, float scaleX, float scaleY) {
    C2D_DrawText(&textData, C2D_AlignLeft, x, y, z, scaleX, scaleY);
}

void Text::DrawWithColor(float x, float y, float z, float scaleX, float scaleY, u32 color) {
    C2D_DrawText(&textData, C2D_WithColor | C2D_AlignLeft, x, y, z, scaleX, scaleY, color);
}

void Text::DrawAligned(u32 flags, float x, float y, float z, float scaleX, float scaleY) {
    C2D_DrawText(&textData, flags, x, y, z, scaleX, scaleY);
}

void Text::DrawWithColorAligned(u32 flags, float x, float y, float z, float scaleX, float scaleY, u32 color) {
    C2D_DrawText(&textData, flags | C2D_WithColor, x, y, z, scaleX, scaleY, color);
}

void Text::GetDimensions(float scaleX, float scaleY, float *outWidth, float *outHeight) const {
    C2D_TextGetDimensions(&textData, scaleX, scaleY, outWidth, outHeight);
}

void Text::SetContent(const std::string &newContent) {
    content = newContent;
    if (staticBuf) {
        C2D_TextBufClear(staticBuf);
        if (font && font->IsLoaded()) {
            C2D_TextFontParse(&textData, font->GetHandle(), staticBuf, content.c_str());
        } else {
            C2D_TextParse(&textData, staticBuf, content.c_str());
        }
        C2D_TextOptimize(&textData);
    }
}

} // namespace xs::text