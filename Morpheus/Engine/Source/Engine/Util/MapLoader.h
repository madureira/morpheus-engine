#pragma once

#include <TiledParser/TileMap.h>
#include <vector>
#include <string>
#include <glm/vec4.hpp>

namespace Morpheus {

	class Tile final
	{
	public:
		glm::vec4 sourceRect;
		glm::vec4 destRect;

		Tile(glm::vec4 _sourceRect, glm::vec4 _destRect)
			: sourceRect(_sourceRect)
			, destRect(_destRect)
		{
		}
	};

	class MapLoader final
	{
	public:
		static const std::vector<Tile*> load(std::string filePath)
		{
			std::vector<Tile*> tiles;

			TiledParser::TileMap map(filePath);
			std::vector<TiledParser::TileSet> tileSets = map.GetTileSets();
			int totalTiles = tileSets[0].GetTileCount();
			int totalColumns = tileSets[0].GetColumns();
			int totalRows = totalTiles / totalColumns;
			int tileWidth = tileSets[0].GetTileWidth();
			int tileHeight = tileSets[0].GetTileHeight();

			for (const auto& layer : map.GetTileLayers())
			{
				int x = 0;
				int y = layer.GetHeight();
				int maxColumns = layer.GetWidth();

				for (const auto& tileIndex : layer.GetTileIds())
				{
					if (tileIndex == 0)
					{
						if (x == maxColumns) {
							x = 0;
							y--;
						}
						x++;
						continue;
					}

					int row = (int)(tileIndex / totalColumns);
					if ((tileIndex % totalColumns) == 0) {
						row--;
					}

					int column = (tileIndex % totalColumns) - 1;
					if (column < 0) {
						column = ((tileIndex - 1) % totalColumns);
					}

					if (x == maxColumns) {
						x = 0;
						y--;
					}

					glm::vec4 source(tileWidth * column, tileHeight * (row + 1), tileWidth * (column + 1), tileHeight * row);
					glm::vec4 destination(tileWidth * x, tileHeight * y, tileWidth, tileHeight);

					Tile* tile = new Tile(source, destination);
					tiles.push_back(tile);

					x++;
				}
			}

			return tiles;
		}
	};
}
