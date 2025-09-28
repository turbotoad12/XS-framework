/**
 * @file xs-framework.h
 * @brief Core framework utilities for XS-runtime.
 *
 * This header includes essential modules for graphics, filesystem, and HID controls,
 * providing a unified interface for the XS-runtime framework.
 */
// --- Graphics includes ---
#include "graphics/colors.hpp"
#include "graphics/screen.hpp"

// --- Filesystem includes ---
#include "fs.hpp"

// --- HID includes ---
#include "hid/controls.hpp"
#include "hid/swkbd.hpp"

// --- Core framework includes ---
#include "sys.hpp"
#include "service.hpp"
#include "errors.hpp"
namespace xs {}