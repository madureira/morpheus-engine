#include "Engine/Engine.h"
#include "Editor/MorpheusEditor.h"

#if defined(_WIN32)
extern "C"
{
	// Forces use of dedicated GPU.
	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

int main()
{
	Morpheus::Engine engine;
	engine.Initialize(new Editor::MorpheusEditor);
	engine.Start();

	return 0;
}
