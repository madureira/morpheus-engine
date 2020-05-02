#include "TileSet.h"

namespace TiledParser {

	TileSet::TileSet(
		int firstGID,
		std::string source,
		std::string tiledVersion,
		float version,
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
	)
		: m_FirstGID(firstGID)
		, m_Source(source)
		, m_TiledVersion(tiledVersion)
		, m_Version(version)
		, m_Type(type)
		, m_Name(name)
		, m_Image(image)
		, m_ImageWidth(imageWidth)
		, m_ImageHeight(imageHeight)
		, m_TileWidth(tileWidth)
		, m_TileHeight(tileHeight)
		, m_TileCount(tileCount)
		, m_Columns(columns)
		, m_Margin(margin)
		, m_Spacing(spacing)
		, m_TransparentColor(transparentColor)
	{
	}

	const int& TileSet::GetFirstGID() const
	{
		return this->m_FirstGID;
	}

	const std::string& TileSet::GetSource() const
	{
		return this->m_Source;
	}

	const std::string& TileSet::GetTiledVersion() const
	{
		return this->m_TiledVersion;
	}

	const float& TileSet::GetVersion() const
	{
		return this->m_Version;
	}

	const std::string& TileSet::GetType() const
	{
		return this->m_Type;
	}

	const std::string& TileSet::GetName() const
	{
		return this->m_Name;
	}

	const std::string& TileSet::GetImage() const
	{
		return this->m_Image;
	}

	const int& TileSet::GetImageWidth() const
	{
		return this->m_ImageWidth;
	}

	const int& TileSet::GetImageHeight() const
	{
		return this->m_ImageHeight;
	}

	const int& TileSet::GetTileWidth() const
	{
		return this->m_TileWidth;
	}

	const int& TileSet::GetTileHeight() const
	{
		return this->m_TileHeight;
	}

	const int& TileSet::GetTileCount() const
	{
		return this->m_TileCount;
	}

	const int& TileSet::GetColumns() const
	{
		return this->m_Columns;
	}

	const int& TileSet::GetMargin() const
	{
		return this->m_Margin;
	}

	const int& TileSet::GetSpacing() const
	{
		return this->m_Spacing;
	}

	const std::string& TileSet::GetTransparentColor() const
	{
		return this->m_TransparentColor;
	}

}
