#include <xs-framework.hpp>

// Using namespaces for convenience
using namespace xs;
using namespace xs::services;

int main(int argc, char *argv[]) {
    xs::sys::Services services(GFX_SERVICE | CONSOLE_TOP);

    hid::Swkbd keyboard(hid::SWKBD_NORMAL, 128);
    keyboard.setHint("Enter a filepath:");
    std::string path;
    Result res = keyboard.getInput(path);
    if (R_FAILED(res)) {
        xs::errors::show(res);
        return 1;
    }
    
    keyboard.setHint("Enter some text:");
    std::string text;
    res = keyboard.getInput(text);
    if (R_FAILED(res)) {
        xs::errors::show(res);
        return 1;
    }

    // Write To the file
    res = xs::fs::WriteFile("sdmc:/" + path, text);
    if (R_SUCCEEDED(res)) {
        printf("Wrote to sdmc:/%s\n", path.c_str());
    } else {
        xs::errors::show(res);
    }

    // Read File
    std::string fileData;
    res = xs::fs::ReadFile("sdmc:/" + path, fileData);
    if (R_SUCCEEDED(res)) {
        printf("File contents:\n%s\n", fileData.c_str());
    } else {
        xs::errors::show(res);
    }

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
