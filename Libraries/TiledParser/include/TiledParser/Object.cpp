#include "Object.h"

namespace TiledParser {

	Object::Object(
		int id,
		std::string name,
		std::string type,
		bool visible,
		int rotation,
		float width,
		float height,
		float x,
		float y,
		std::vector<Point> polygon
	)
		: m_Id(id)
		, m_Name(name)
		, m_Type(type)
		, m_Visible(visible)
		, m_Rotation(rotation)
		, m_Width(width)
		, m_Height(height)
		, m_X(x)
		, m_Y(y)
		, m_Polygon(polygon)
	{
	}

	const int& Object::GetId() const
	{
		return this->m_Id;
	}

	const std::string& Object::GetName() const
	{
		return this->m_Name;
	}

	const std::string& Object::GetType() const
	{
		return this->m_Type;
	}

	const bool& Object::IsVisible() const
	{
		return this->m_Visible;
	}

	const int& Object::GetRotation() const
	{
		return this->m_Rotation;
	}

	const float& Object::GetWidth() const
	{
		return this->m_Width;
	}

	const float& Object::GetHeight() const
	{
		return this->m_Height;
	}

	const float& Object::GetX() const
	{
		return this->m_X;
	}

	const float& Object::GetY() const
	{
		return this->m_Y;
	}

	const std::vector<Point>& Object::GetPolygon() const
	{
		return this->m_Polygon;
	}

}
