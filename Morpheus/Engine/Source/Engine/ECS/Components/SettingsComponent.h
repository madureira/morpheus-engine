#pragma once

#include <string>

namespace Morpheus {

	struct SettingsComponent final
	{
		std::string windowTitle;
		bool isWindowFullScreen;
		bool isPrimaryMonitor;
		unsigned int windowWidth;
		unsigned int windowHeight;
		unsigned int maxFPS;
		bool isVSyncOn;
		bool isDebug;
	};

}
