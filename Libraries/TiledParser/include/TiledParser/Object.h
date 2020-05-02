#pragma once

#include <string>
#include <vector>

namespace TiledParser {

	struct Point
	{
		float x;
		float y;
	};

	class Object final
	{
	private:
		int m_Id;
		std::string m_Name;
		std::string m_Type;
		bool m_Visible;
		int m_Rotation;
		float m_Width;
		float m_Height;
		float m_X;
		float m_Y;
		std::vector<Point> m_Polygon;

	public:
		Object(
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
		);

		const int& GetId() const;
		const std::string& GetName() const;
		const std::string& GetType() const;
		const bool& IsVisible() const;
		const int& GetRotation() const;
		const float& GetWidth() const;
		const float& GetHeight() const;
		const float& GetX() const;
		const float& GetY() const;
		const std::vector<Point>& GetPolygon() const;

		inline const bool IsRectangle() const
		{
			return m_Type == "rectangle";
		}

		inline const bool IsPolygon() const
		{
			return m_Type == "polygon";
		}

		inline const bool IsPoint() const
		{
			return m_Type == "point";
		}

		inline const bool IsEllipse() const
		{
			return m_Type == "ellipse";
		}
	};

}
