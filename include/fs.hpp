/**
 * @file sdmc.h
 * @brief SDMC (SD Card) related utilities.
 */
#pragma once

#include <3ds.h>
#include <string>

/**
 * @brief Filesystem-related utilities.
 *
 */
namespace xs::fs {
/**
 * @brief Appends data to a file (creates the file if it doesn't exist).
 *
 * @param path Path
 * @param data Data to append to the file.
 */
void AppendFile(const std::string &path, const std::string &data);

/**
 * @brief Reads the entire contents of a file into a string.
 *
 * @param path Path
 * @return std::string File contents (empty on error or if file missing).
 */
std::string ReadFile(const std::string &path);

/**
 * @brief Writes data to a file, overwriting any existing contents.
 *
 * @param path Path
 * @param data Data to write to the file.
 */
void WriteFile(const std::string &path, const std::string &data);

} // namespace xs::fs