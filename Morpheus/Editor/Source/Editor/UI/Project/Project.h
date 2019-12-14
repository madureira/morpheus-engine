#pragma once

#include "Editor/UI/UIComponent.h"
#include "Editor/UI/TreeView/TreeView.h"

namespace Editor {

	class Project : public UIComponent
	{
	private:
		TreeView* m_TreeView;

	public:
		Project();
		void Draw(entt::registry& registry) override;
	};

}
