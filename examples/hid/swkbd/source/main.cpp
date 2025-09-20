#include <xs-framework.h>
#include <hid/swkbd.h>
// Using namespaces for convenience
using namespace xs;
using namespace xs::services;

int main(int argc, char* argv[])
{
	xs::sys::Services services(GFX_SERVICE | CONSOLE_TOP);

	xs::hid::Swkbd keyboard(xs::hid::SWKBD_NORMAL, 128);
	keyboard.setHint("Enter some text:");
	keyboard.setValidation(SWKBD_NOTEMPTY);
	std::string input = keyboard.getInput();
	if (!input.empty()) {
		printf("You entered: %s\n", input.c_str());
	} else {
		printf("No input or cancelled.\n");
	}
	// Main loop
	while (xs::sys::MainLoop())
	{
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
