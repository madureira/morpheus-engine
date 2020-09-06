#pragma once

#include <Engine/App.h>
#include <Engine/Window/Window.h>

namespace Editor {

    class Menubar;
    class Actionbar;
    class Dock;
    class Footer;

    class MorpheusEditor final : public Morpheus::App
    {
    private:
        Menubar* m_Menubar;
        Actionbar* m_Actionbar;
        Dock* m_Dock;
        Footer* m_Footer;

    public:
        MorpheusEditor();
        ~MorpheusEditor();

        void Initialize(entt::registry& registry) override;
        void OnFrameStarted(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) override;
        void FrameListener(entt::registry& registry, double deltaTime, int currentFrame, int frameRate) override;
    };

}
