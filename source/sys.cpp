#include "sys.h"

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

    /**
     * @brief 3DS Notification utilities.
     */
    class News {
    public:
        /// Initializes the NEWS service.
        News() {
            newsInit();   // start NEWS service
        }

        /// Cleans up the NEWS service.
        ~News() {
            newsExit();   // clean up NEWS service
        }

        /**
         * @brief Add a text notification (no image).
         * 
         * @param title Title text
         * @param message Message text
         * @return true if notification was added successfully
         */
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

    private:
        /// Basic ASCII-only UTF-8 → UTF-16 converter
        void utf8ToUtf16(u16* dst, const char* src, size_t maxChars) {
            size_t i;
            for (i = 0; i < maxChars && src[i] != '\0'; i++) {
                dst[i] = static_cast<u16>(src[i]);
            }
            dst[i] = 0;
        }
    };
    

}
