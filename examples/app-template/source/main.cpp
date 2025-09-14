#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xs-framework.h>

using namespace xs;

int main(int argc, char* argv[])
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	printf("Hello, world!\n");

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

	gfxExit();
	return 0;
}
