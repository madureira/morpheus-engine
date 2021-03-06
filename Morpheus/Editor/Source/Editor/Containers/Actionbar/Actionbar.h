#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

    class Actionbar final : public UIContainer
    {
    private:
        bool m_IsPlaying;

    public:
        Actionbar();

        void Render(entt::registry &registry) override;
    };

}
