#include "fs.hpp"

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
 * @param path The path to the file.
 * @param data The string to append to the file content.
 * @return Result RL_SUCCESS on success, or an error code on failure
 */
Result AppendFile(const std::string &path, const std::string &data) {
    FILE *file = fopen(path.c_str(), "a");
    if (!file) {
        return MAKERESULT(RL_PERMANENT, RS_NOTFOUND, RM_APPLICATION, RD_NOT_FOUND);
    }
    
    size_t written = fwrite(data.c_str(), sizeof(char), data.size(), file);
    fclose(file);
    
    if (written != data.size()) {
        return MAKERESULT(RL_PERMANENT, RS_INTERNAL, RM_APPLICATION, RD_NO_DATA);
    }
    
    return MAKERESULT(RL_SUCCESS, RS_SUCCESS, RM_APPLICATION, RD_SUCCESS);
}
/**
 * @brief Reads the entire content of a file into a string.
 *
 * @param path The path to the file.
 * @param outData Output string to store file contents
 * @return Result RL_SUCCESS on success, or an error code on failure
 */
Result ReadFile(const std::string &path, std::string &outData) {
    FILE *file = fopen(path.c_str(), "r");
    if (!file) {
        return MAKERESULT(RL_PERMANENT, RS_NOTFOUND, RM_APPLICATION, RD_NOT_FOUND);
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size < 0) {
        fclose(file);
        return MAKERESULT(RL_PERMANENT, RS_INTERNAL, RM_APPLICATION, RD_INVALID_SIZE);
    }
    fseek(file, 0, SEEK_SET);
    
    outData.resize(size);
    size_t bytesRead = fread(&outData[0], sizeof(char), size, file);
    fclose(file);
    
    if (bytesRead != static_cast<size_t>(size)) {
        return MAKERESULT(RL_PERMANENT, RS_INTERNAL, RM_APPLICATION, RD_NO_DATA);
    }
    
    return MAKERESULT(RL_SUCCESS, RS_SUCCESS, RM_APPLICATION, RD_SUCCESS);
}
/**
 * @brief Writes a string to a file, overwriting existing content.
 * @param path The path to the file.
 * @param data The string to write to the file.
 * @return Result RL_SUCCESS on success, or an error code on failure
 */
Result WriteFile(const std::string &path, const std::string &data) {
    FILE *file = fopen(path.c_str(), "w");
    if (!file) {
        return MAKERESULT(RL_PERMANENT, RS_NOTFOUND, RM_APPLICATION, RD_NOT_FOUND);
    }
    
    size_t written = fwrite(data.c_str(), sizeof(char), data.size(), file);
    fclose(file);
    
    if (written != data.size()) {
        return MAKERESULT(RL_PERMANENT, RS_INTERNAL, RM_APPLICATION, RD_NO_DATA);
    }
    
    return MAKERESULT(RL_SUCCESS, RS_SUCCESS, RM_APPLICATION, RD_SUCCESS);
}

} // namespace xs::fs