#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include "Vendors/IconsFontAwesome5/IconsFontAwesome5.h"
#include "Engine/ECS/ECS.h"
#include "Engine/Log/Log.h"

namespace Editor {

	class UIComponent {
	public:
		virtual ~UIComponent() = default;
		virtual void Draw(entt::registry& registry) = 0;
	};

}
