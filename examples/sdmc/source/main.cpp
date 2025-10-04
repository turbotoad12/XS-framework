#include <xs-framework.hpp>

// Using namespaces for convenience
using namespace xs;
using namespace xs::services;

int main(int argc, char *argv[]) {
  xs::sys::Services services(GFX_SERVICE | CONSOLE_TOP);

  hid::Swkbd keyboard(hid::SWKBD_NORMAL, 128);
  keyboard.setHint("Enter a filepath:");
  std::string path = keyboard.getInput();
  keyboard.setHint("Enter some text:");
  std::string text = keyboard.getInput();

  // Write To the file
  xs::fs::WriteFile("sdmc:/" + path, text);
  printf("Wrote to sdmc:/ %s\n", path.c_str());

  // Read FIle
  std::string fileData = xs::fs::ReadFile("sdmc:/" + path);
  if (!fileData.empty()) {
    printf("File contents:\n%s\n", fileData.c_str());
  } else {
    printf("File is empty or missing.\n");
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
