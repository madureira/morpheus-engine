#include "ObjectGroup.h"

namespace TiledParser {

	ObjectGroup::ObjectGroup(
		int id,
		std::string name,
		std::string type,
		float opacity,
		bool visible,
		int x,
		int y,
		std::string drawOrder,
		std::vector<Object> objects
	)
		: Layer{
			id,
			name,
			type,
			opacity,
			visible,
			x,
			y
		}
		, m_DrawOrder(drawOrder)
		, m_Objects(objects)
	{
	}

	const std::string& ObjectGroup::GetDrawOrder() const
	{
		return this->m_DrawOrder;
	}

	const std::vector<Object>& ObjectGroup::GetObjects() const
	{
		return this->m_Objects;
	}

}
