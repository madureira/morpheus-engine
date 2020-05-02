#pragma once

#include "Layer.h"
#include <string>
#include <vector>

namespace TiledParser {

	class TileLayer final : public Layer
	{
	private:
		std::string m_Compression;
		std::string m_Encoding;
		int m_Width;
		int m_Height;
		std::vector<int> m_TileIds;

	public:
		TileLayer(
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
		);

		const std::string& GetCompression() const;
		const std::string& GetEncoding() const;
		const int& GetWidth() const;
		const int& GetHeight() const;
		const std::vector<int>& GetTileIds() const;
	};

}
