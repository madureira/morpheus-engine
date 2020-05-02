#pragma once

#include "Layer.h"
#include "Object.h"
#include <string>
#include <vector>

namespace TiledParser {

	class ObjectGroup final : public Layer
	{
	private:
		std::string m_DrawOrder;
		std::vector<Object> m_Objects;

	public:
		ObjectGroup(
			int id,
			std::string name,
			std::string type,
			float opacity,
			bool visible,
			int x,
			int y,
			std::string drawOrder,
			std::vector<Object> objects
		);

		const std::string& GetDrawOrder() const;
		const std::vector<Object>& GetObjects() const;
	};

}
