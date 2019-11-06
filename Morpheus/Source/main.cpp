#include "Window/Window.h"

int main()
{
	Morpheus::Window window("Test", 1024, 768, true);

	while (window.IsOpen())
	{
		window.PollEvents();
		// render
		window.SwapBuffers();
	}

	return 0;
}
