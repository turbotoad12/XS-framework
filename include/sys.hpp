/**
 * @file sys.h
 * @brief System-related utilities.
 */
#pragma once

#include <3ds.h>
#include <string>
#include <vector>

/**
 * @brief System-related utilities.
 */
namespace xs::sys {

/**
 * @brief Checks if the current system is a New 3DS.
 *
 * @return true if running on a New 3DS, false otherwise
 */
bool isNew3DS();

/**
 * @brief Main Loop. Run this every frame!
 *
 * @return true
 */
bool MainLoop() {
  aptMainLoop();
  return true;
}

/**
 * @brief 3DS Notification utilities.
 */
namespace news {
/**
 * @brief Add a text notification (no image).
 * @param title Title text
 * @param message Message text
 * @return true if notification was added successfully
 */
bool addNotification(const std::string &title, const std::string &message);
/// Basic ASCII-only UTF-8 → UTF-16 converter
void utf8ToUtf16(u16 *dst, const char *src, size_t maxChars);

}; // namespace news

} // namespace xs::sys
