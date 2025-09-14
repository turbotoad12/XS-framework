#pragma once

#include <3ds.h>
#include <cstdint>

namespace xs {
	namespace services {
		// Flags for services
		constexpr uint32_t GFX_SERVICE    = (1 << 0);
		constexpr uint32_t NEWS_SERVICE   = (1 << 1);
		constexpr uint32_t CONSOLE_TOP    = (1 << 2);
		constexpr uint32_t CONSOLE_BOTTOM = (1 << 3);
	}
}

namespace xs::sys {

class Services {
	uint32_t flags = 0;

public:
	explicit Services(uint32_t f = 0);
	~Services();

	void enable(uint32_t f);
	void disable(uint32_t f);
};

} // namespace xs::sys

