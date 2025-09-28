#include "sys.hpp"
#include "service.hpp"
/**
 * @brief System-related utilities.
 */
namespace xs::sys {

    /**
     * @brief Checks if the current system is a New 3DS.
     * 
     * @return true if running on a New 3DS, false otherwise
     */
    bool isNew3DS() {
        bool out = false;
        APT_CheckNew3DS(&out);
        return out;
    }
    // Implementations for xs::sys::News declared in include/sys.h
    namespace news {
    bool addNotification(const std::string& title, const std::string& message) {
        std::vector<u16> title16(title.size() + 1);
        std::vector<u16> message16(message.size() + 1);

        utf8ToUtf16(title16.data(), title.c_str(), title.size());
        utf8ToUtf16(message16.data(), message.c_str(), message.size());

        Result res = NEWS_AddNotification(
            title16.data(),  title.size(),
            message16.data(), message.size(),
            nullptr, 0,
            false
        );
        return R_SUCCEEDED(res);
    }

    void utf8ToUtf16(u16* dst, const char* src, size_t maxChars) {
        size_t i;
        for (i = 0; i < maxChars && src[i] != '\0'; i++) {
            dst[i] = static_cast<u16>(src[i]);
        }
        dst[i] = 0;
    }
}
}
