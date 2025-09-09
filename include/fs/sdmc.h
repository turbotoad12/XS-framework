/**
 * @file sdmc.h
 * @brief SDMC (SD Card) related utilities.
 */
#pragma once

#include <3ds.h>
#include <string>

namespace xs::fs {

    /**
     * @brief SDMC (SD Card) related utilities.
     *
     * Functions in this namespace operate on paths relative to the SD card
     * and provide simple file read/write helpers used by the framework.
     */
    namespace sdmc {

        /**
         * @brief Appends data to a file (creates the file if it doesn't exist).
         *
         * @param path Path relative to the SD card (e.g. "folder/file.txt").
         * @param data Data to append to the file.
         */
        void AppendFile(const std::string& path, const std::string& data);

        /**
         * @brief Reads the entire contents of a file into a string.
         *
         * @param path Path relative to the SD card.
         * @return std::string File contents (empty on error or if file missing).
         */
        std::string ReadFile(const std::string& path);

        /**
         * @brief Writes data to a file, overwriting any existing contents.
         *
         * @param path Path relative to the SD card.
         * @param data Data to write to the file.
         */
        void WriteFile(const std::string& path, const std::string& data);

        /**
         * @brief Helper that returns a full SDMC path (prefixes with "sdmc:/").
         *
         * @param path Path relative to the SD card.
         * @return std::string Full SDMC path.
         */
        std::string GetSdmcPath(const std::string& path);
    }
}