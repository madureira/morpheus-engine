#include <Engine/Engine.h>
#include "Editor/MorpheusEditor.h"

#ifdef _WIN32
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
    Editor::MorpheusEditor editor;

    engine.Initialize(&editor);
    engine.Start();

    return 0;
}
