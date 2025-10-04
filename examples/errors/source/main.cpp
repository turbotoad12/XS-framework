#include <xs-framework.hpp>

// Using namespaces for convenience
using namespace xs;
using namespace xs::services;

void printMenu() {
  printf("Press A to show decoded error.\n");
  printf("Press B to show custom error.\n");
  printf("Press X to show custom error with software reset.\n");
  printf("Press START to exit.\n");
}
int main(int argc, char *argv[]) {
  xs::sys::Services services(GFX_SERVICE | CONSOLE_TOP);

  printMenu();

  // Main loop
  while (xs::sys::MainLoop()) {
    graphics::screen::WaitForScreen();
    graphics::screen::SwapFrameBuffers();
    hid::control::ScanInput();

    // Your code goes here
    u32 kDown = hid::control::GetKeysPressed();
    if (kDown & KEY_START)
      break; // break in order to return to hbmenu
    else if (kDown & KEY_A) {
      Result rc = MAKERESULT(RL_PERMANENT, 1, 0,
                             RD_NOT_IMPLEMENTED); // example error code
      xs::errors::show(rc);
      graphics::screen::ClearConsole();
      printMenu();
    } else if (kDown & KEY_B) {
      xs::errors::show("This is a custom error message!");
      graphics::screen::ClearConsole();
      printMenu();
    } else if (kDown & KEY_X) {
      xs::errors::show("This is a custom error message with software reset!",
                       true);
      graphics::screen::ClearConsole();
      printMenu();
    }
  }

  return 0;
}
