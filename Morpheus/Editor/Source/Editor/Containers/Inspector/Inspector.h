#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

    class Inspector final : public UIContainer
    {
    public:
        void Render(entt::registry& registry) override;
    };

}
