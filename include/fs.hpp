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
 * @return Result RL_SUCCESS on success, or an error code on failure
 */
Result AppendFile(const std::string &path, const std::string &data);

/**
 * @brief Reads the entire contents of a file into a string.
 *
 * @param path Path
 * @param outData Output string to store file contents
 * @return Result RL_SUCCESS on success, or an error code on failure
 */
Result ReadFile(const std::string &path, std::string &outData);

/**
 * @brief Writes data to a file, overwriting any existing contents.
 *
 * @param path Path
 * @param data Data to write to the file.
 * @return Result RL_SUCCESS on success, or an error code on failure
 */
Result WriteFile(const std::string &path, const std::string &data);

} // namespace xs::fs