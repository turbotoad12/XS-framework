#include <xs-framework.hpp>

// Using namespaces for convenience
using namespace xs;
using namespace xs::services;

int main(int argc, char *argv[]) {
    xs::sys::Services services(GFX_SERVICE | CONSOLE_TOP);

    printf("Hello, world!\n");

    // Main loop
    while (xs::sys::MainLoop()) {
        graphics::screen::WaitForScreen();
        graphics::screen::SwapFrameBuffers();
        hid::control::ScanInput();

        // Your code goes here
        u32 kDown = hid::control::GetKeysPressed();
        if (kDown & KEY_START)
            break; // break in order to return to hbmenu
    }

    return 0;
}
