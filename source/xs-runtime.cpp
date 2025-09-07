#include <3ds.h>

namespace xs {
    namespace os {
        bool isNew3DS() {
        bool out = false;
        APT_CheckNew3DS(&out);
        return out;
    }
}
}
