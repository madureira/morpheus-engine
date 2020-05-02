#pragma once

#include <string>
#include <vector>
#include "Layer.h"
#include "TileLayer.h"
#include "TileSet.h"
#include "ObjectGroup.h"

namespace TiledParser {

	class TileMap final
	{
	private:
		std::string m_FilePath;
		float m_Version;
		int m_CompressionLevel;
		std::string m_Type;
		std::string m_Orientation;
		std::string m_RenderOrder;
		int m_Width;
		int m_Height;
		int m_NextLayerId;
		int m_NextObjectId;
		std::string m_TiledVersion;
		int m_TileWidth;
		int m_TileHeight;
		std::string m_BackgroundColor;
		std::vector<TileSet> m_TileSets;
		std::vector<TileLayer> m_TileLayers;
		std::vector<ObjectGroup> m_ObjectGroups;

	public:
		TileMap(std::string filePath);

		const float& GetVersion() const;
		const std::string& GetType() const;
		const int& GetCompressionLevel() const;
		const std::string& GetOrientation() const;
		const std::string& GetRenderOrder() const;
		const int& GetWidth() const;
		const int& GetHeight() const;
		const int& GetNextLayerId() const;
		const int& GetNextObjectId() const;
		const std::string& GetTiledVersion() const;
		const int& GetTileWidth() const;
		const int& GetTileHeight() const;
		const std::string& GetBackgroundColor() const;
		const std::vector<TileSet>& GetTileSets() const;
		const std::vector<TileLayer>& GetTileLayers() const;
		const std::vector<ObjectGroup>& GetObjectGroups() const;

	private:
		const std::string ReadJSONFile(std::string& filePath);
		const bool Parse(std::string& jsonStr);
	};

}
