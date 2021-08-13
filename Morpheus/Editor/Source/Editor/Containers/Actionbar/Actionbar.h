#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

    class Actionbar final : public UIContainer
    {
    public:
        Actionbar();

        void Render(entt::registry &registry) override;
    };

}
