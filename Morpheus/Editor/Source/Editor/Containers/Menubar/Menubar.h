#pragma once

#include "Editor/Containers/UIContainer.h"

namespace Editor {

    class NewProject;
    class NewScene;

    class Menubar final : public UIContainer
    {
    private:
        NewProject* m_NewProject;
        NewScene* m_NewScene;

    public:
        Menubar();
        ~Menubar();

        void Render(entt::registry& registry) override;
    };

}
