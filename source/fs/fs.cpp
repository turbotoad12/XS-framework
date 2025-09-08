#include "fs/fs.h"


/**
 * @brief Filesystem-related utilities.
 *
 */
namespace xs::fs {

    /**
     * @brief SDMC (SD Card) related utilities.
     *
     */
    namespace sdmc {
        /**
         * @brief Reads the entire content of a file into a string.
         *
         * @param path The path to the file.
         * @param data The string to append to the file content.
         */
        void AppendFile(const std::string& path, const std::string& data) {
            FILE* file = fopen(sdmc::GetSdmcPath(path).c_str(), "a");
            if (file) {
                fwrite(data.c_str(), sizeof(char), data.size(), file);
                fclose(file);
            }
        }
        /**
         * @brief Reads the entire content of a file into a string.
         *
         * @param path The path to the file.
         * @return std::string The content of the file.
         */
        std::string ReadFile(const std::string& path) {
            std::string content;
            FILE* file = fopen(sdmc::GetSdmcPath(path).c_str(), "r");
            if (file) {
                fseek(file, 0, SEEK_END);
                long size = ftell(file);
                fseek(file, 0, SEEK_SET);
                content.resize(size);
                fread(&content[0], sizeof(char), size, file);
                fclose(file);
            }
            return content;
        }
        /**
         * @brief Writes a string to a file, overwriting existing content.
         * @param path The path to the file.
         * @param data The string to write to the file.
         */
        void WriteFile(const std::string& path, const std::string& data) {
            FILE* file = fopen(sdmc::GetSdmcPath(path).c_str(), "w");
            if (file) {
                fwrite(data.c_str(), sizeof(char), data.size(), file);
                fclose(file);
            }
        }
        std::string GetSdmcPath(const std::string& path) {
            return "sdmc:/" + path;
        }
    }
}