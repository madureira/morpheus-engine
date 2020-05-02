#pragma once

#include <string>

namespace TiledParser {

	class TileSet final
	{
	private:
		int m_FirstGID;
		std::string m_Source;
		std::string m_TiledVersion;
		float m_Version;
		std::string m_Type;
		std::string m_Name;
		std::string m_Image;
		int m_ImageWidth;
		int m_ImageHeight;
		int m_TileWidth;
		int m_TileHeight;
		int m_TileCount;
		int m_Columns;
		int m_Margin;
		int m_Spacing;
		std::string m_TransparentColor;

	public:
		TileSet(
			int firstGID,
			std::string source,
			std::string tiledVersion,
			float m_Version,
			std::string type,
			std::string name,
			std::string image,
			int imageWidth,
			int imageHeight,
			int tileWidth,
			int tileHeight,
			int tileCount,
			int columns,
			int margin,
			int spacing,
			std::string transparentColor
		);

		const int& GetFirstGID() const;
		const std::string& GetSource() const;
		const std::string& GetTiledVersion() const;
		const float& GetVersion() const;
		const std::string& GetType() const;
		const std::string& GetName() const;
		const std::string& GetImage() const;
		const int& GetImageWidth() const;
		const int& GetImageHeight() const;
		const int& GetTileWidth() const;
		const int& GetTileHeight() const;
		const int& GetTileCount() const;
		const int& GetColumns() const;
		const int& GetMargin() const;
		const int& GetSpacing() const;
		const std::string& GetTransparentColor() const;
	};

}
