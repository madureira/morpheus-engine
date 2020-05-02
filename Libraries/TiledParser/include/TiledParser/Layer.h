#pragma once

#include <string>
#include <vector>

namespace TiledParser {

	class Layer
	{
	private:
		int m_Id;
		std::string m_Name;
		std::string m_Type;
		float m_Opacity;
		bool m_Visible;
		int m_X;
		int m_Y;

	public:
		Layer(
			int id,
			std::string name,
			std::string type,
			float opacity,
			bool visible,
			int x,
			int y
		);

		const int& GetId() const;
		const std::string& GetName() const;
		const std::string& GetType() const;
		const float& GetOpacity() const;
		const bool& IsVisible() const;
		const int& GetX() const;
		const int& GetY() const;
	};

}
