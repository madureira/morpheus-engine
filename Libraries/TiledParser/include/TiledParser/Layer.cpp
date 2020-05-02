#include "Layer.h"
#include <string>

namespace TiledParser {

	Layer::Layer(
		int id,
		std::string name,
		std::string type,
		float opacity,
		bool visible,
		int x,
		int y
	)
		: m_Id(id)
		, m_Name(name)
		, m_Type(type)
		, m_Opacity(opacity)
		, m_Visible(visible)
		, m_X(x)
		, m_Y(y)
	{
	}

	const int& Layer::GetId() const
	{
		return this->m_Id;
	}

	const std::string& Layer::GetName() const
	{
		return this->m_Name;
	}

	const std::string& Layer::GetType() const
	{
		return this->m_Type;
	}

	const float& Layer::GetOpacity() const
	{
		return this->m_Opacity;
	}

	const bool& Layer::IsVisible() const
	{
		return this->m_Visible;
	}

	const int& Layer::GetX() const
	{
		return this->m_X;
	}

	const int& Layer::GetY() const
	{
		return this->m_Y;
	}

}
