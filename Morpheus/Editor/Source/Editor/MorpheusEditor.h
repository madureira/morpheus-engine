#pragma once

#include <Engine/App.h>
#include <Engine/Window/Window.h>
#include "Editor/Containers/Dock/Dock.h"
#include "Editor/Containers/Footer/Footer.h"
#include "Editor/Containers/Menubar/Menubar.h"
#include "Editor/Containers/Actionbar/Actionbar.h"

namespace Editor {

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
