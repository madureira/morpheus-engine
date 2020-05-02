#include "TileLayer.h"

namespace TiledParser {

	TileLayer::TileLayer(
		int id,
		std::string name,
		std::string compression,
		std::string encoding,
		std::string type,
		int width,
		int height,
		float opacity,
		bool visible,
		int x,
		int y,
		std::vector<int> tileIds
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
		, m_Compression(compression)
		, m_Encoding(encoding)
		, m_Width(width)
		, m_Height(height)
		, m_TileIds(tileIds)
	{
	}

	const std::string& TileLayer::GetCompression() const
	{
		return this->m_Compression;
	}

	const std::string& TileLayer::GetEncoding() const
	{
		return this->m_Encoding;
	}

	const int& TileLayer::GetWidth() const
	{
		return this->m_Width;
	}

	const int& TileLayer::GetHeight() const
	{
		return this->m_Height;
	}

	const std::vector<int>& TileLayer::GetTileIds() const
	{
		return this->m_TileIds;
	}

}
