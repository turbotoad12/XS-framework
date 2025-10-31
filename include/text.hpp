#pragma once

#include <3ds.h>
#include <citro2d.h>
#include <string>

namespace xs::text {
/**
 * @class Font
 * @brief Wrapper class for citro2d font management.
 *
 * This class provides RAII-style management for C2D_Font objects,
 * automatically handling resource allocation and deallocation.
 */
class Font {
  public:
    /**
     * @brief Constructs a Font object by loading a font from a file.
     * @param fontpath Path to the font file to load.
     *
     * Loads a font file using C2D_FontLoad. The font data will be
     * automatically freed when the object is destroyed.
     * Use GetLoadResult() to check if loading was successful.
     */
    explicit Font(const std::string &fontpath);

    /**
     * @brief Destructor that automatically frees the font data.
     *
     * Ensures the underlying C2D_Font resource is properly freed
     * using C2D_FontFree.
     */
    ~Font();

    /**
     * @brief Manually frees the font data before destruction.
     *
     * This method allows early release of font resources. After calling
     * this method, the font handle becomes null and the destructor will
     * not attempt to free it again.
     */
    void Free();

    /**
     * @brief Gets the underlying C2D_Font handle.
     * @return The C2D_Font handle managed by this object.
     *
     * Provides access to the raw citro2d font handle for use with
     * low-level citro2d functions.
     */
    C2D_Font GetHandle() const;

  /**
   * @brief Returns true if the font was successfully loaded.
   */
  bool IsLoaded() const;

    /**
     * @brief Gets the result of the font loading operation.
     * @return Result RL_SUCCESS on success, or an error code on failure
     */
    Result GetLoadResult() const;

    /**
     * @brief Copy constructor (deleted).
     *
     * Font objects cannot be copied to prevent double-free errors.
     */
    Font(const Font &) = delete;

    /**
     * @brief Copy assignment operator (deleted).
     *
     * Font objects cannot be copy-assigned to prevent double-free errors.
     */
    Font &operator=(const Font &) = delete;

  private:
  C2D_Font fontData = nullptr; ///< Internal citro2d font handle
  Result loadResult; ///< Result of the font loading operation
};

/**
 * @class Text
 * @brief Wrapper class for citro2d text rendering with support for custom and system fonts.
 *
 * This class manages text buffers and provides convenient methods for drawing
 * text with various options including colors, alignment, and scaling. It supports
 * both custom fonts and the 3DS system font.
 */
class Text {
  public:
    /**
     * @brief Constructs a Text object with a custom font.
     * @param content The text string to render.
     * @param font Pointer to a Font object to use for rendering.
     *
     * Creates a text buffer with 4096 glyph capacity and parses the provided
     * content using the specified font. The text is automatically optimized
     * for efficient rendering.
     *
     * @note The font pointer must remain valid for the lifetime of this Text object.
     */
    Text(const std::string &content, Font *font);

    /**
     * @brief Constructs a Text object with the system font.
     * @param content The text string to render.
     *
     * Creates a text buffer with 4096 glyph capacity and parses the provided
     * content using the 3DS system font. The text is automatically optimized
     * for efficient rendering.
     *
     * @note The default 3DS system font has a glyph height of 30px with the
     *       baseline at 25px.
     */
    explicit Text(const std::string &content);

    /**
     * @brief Destructor that frees the text buffer.
     *
     * Automatically releases the text buffer resources using C2D_TextBufDelete.
     */
    ~Text();

    /**
     * @brief Draws text with basic parameters and left alignment.
     * @param x Horizontal position to draw the text.
     * @param y Vertical position (top-left corner of text block).
     * @param z Depth value for z-ordering (default: 0.0f).
     * @param scaleX Horizontal scale factor (default: 1.0f, native font size).
     * @param scaleY Vertical scale factor (default: 1.0f, native font size).
     *
     * Renders the text at the specified position with left alignment.
     * Use scale values > 1.0f to enlarge text, < 1.0f to shrink it.
     */
    void Draw(float x, float y, float z = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f);

    /**
     * @brief Draws text with a specified color and left alignment.
     * @param x Horizontal position to draw the text.
     * @param y Vertical position (top-left corner of text block).
     * @param z Depth value for z-ordering.
     * @param scaleX Horizontal scale factor.
     * @param scaleY Vertical scale factor.
     * @param color Color value in u32 RGBA8 format (0xRRGGBBAA).
     *
     * Renders the text with the specified color. The color format uses
     * 8 bits per channel (red, green, blue, alpha).
     *
     * @note Example colors: 0xFFFFFFFF (white), 0x000000FF (black),
     *       0xFF0000FF (red), 0x00FF00FF (green), 0x0000FFFF (blue).
     */
    void DrawWithColor(float x, float y, float z, float scaleX, float scaleY, u32 color);

    /**
     * @brief Draws text with custom alignment flags.
     * @param flags Alignment and rendering flags (e.g., C2D_AlignLeft, C2D_AlignRight,
     *              C2D_AlignCenter, C2D_AlignJustified, C2D_AtBaseline, C2D_WordWrap).
     * @param x Horizontal position to draw the text.
     * @param y Vertical position. Interpretation depends on alignment flags.
     * @param z Depth value for z-ordering.
     * @param scaleX Horizontal scale factor.
     * @param scaleY Vertical scale factor.
     *
     * Provides full control over text alignment and rendering options:
     * - C2D_AlignLeft: Align to the left (default)
     * - C2D_AlignRight: Align to the right
     * - C2D_AlignCenter: Center the text
     * - C2D_AlignJustified: Justify the text
     * - C2D_AtBaseline: Y coordinate matches the baseline instead of top
     * - C2D_WordWrap: Enable word wrapping (requires additional width parameter)
     *
     * Flags can be combined using the bitwise OR operator (|).
     */
    void DrawAligned(u32 flags, float x, float y, float z, float scaleX, float scaleY);

    /**
     * @brief Draws text with color and custom alignment.
     * @param flags Alignment and rendering flags (e.g., C2D_AlignLeft, C2D_AlignRight,
     *              C2D_AlignCenter, C2D_AlignJustified, C2D_AtBaseline, C2D_WordWrap).
     * @param x Horizontal position to draw the text.
     * @param y Vertical position. Interpretation depends on alignment flags.
     * @param z Depth value for z-ordering.
     * @param scaleX Horizontal scale factor.
     * @param scaleY Vertical scale factor.
     * @param color Color value in u32 RGBA8 format (0xRRGGBBAA).
     *
     * Combines color rendering with custom alignment options. See DrawAligned()
     * for details on alignment flags and DrawWithColor() for color format.
     *
     * @note The C2D_WithColor flag is automatically added to the provided flags.
     */
    void DrawWithColorAligned(u32 flags, float x, float y, float z, float scaleX, float scaleY, u32 color);

    /**
     * @brief Gets the dimensions of the rendered text.
     * @param scaleX Horizontal scale factor to calculate dimensions for.
     * @param scaleY Vertical scale factor to calculate dimensions for.
     * @param outWidth Pointer to store the calculated width (can be nullptr to skip).
     * @param outHeight Pointer to store the calculated height (can be nullptr to skip).
     *
     * Calculates the bounding box dimensions of the text when rendered with
     * the specified scale factors. This is useful for layout calculations,
     * centering text, or creating text boxes.
     *
     * @note Pass nullptr for outWidth or outHeight if you only need one dimension.
     */
    void GetDimensions(float scaleX, float scaleY, float *outWidth, float *outHeight) const;

    /**
     * @brief Updates the text content and re-parses it.
     * @param newContent The new text string to render.
     *
     * Clears the existing text buffer, parses the new content, and optimizes
     * it for rendering. This allows dynamic text updates without creating a
     * new Text object.
     *
     * @note This operation clears and re-parses the entire text buffer, which
     *       may impact performance if called frequently. The same font (custom
     *       or system) used during construction will be used for the new content.
     */
    void SetContent(const std::string &newContent);

    /**
     * @brief Copy constructor (deleted).
     *
     * Text objects cannot be copied to prevent issues with shared text buffers.
     */
    Text(const Text &) = delete;

    /**
     * @brief Copy assignment operator (deleted).
     *
     * Text objects cannot be copy-assigned to prevent issues with shared text buffers.
     */
    Text &operator=(const Text &) = delete;

  private:
    std::string content;   ///< Text content string
    Font *font;            ///< Pointer to custom font (nullptr for system font)
    C2D_TextBuf staticBuf; ///< Text buffer for storing glyphs (up to 4096)
    C2D_Text textData;     ///< Parsed text data structure for rendering
};
} // namespace xs::text