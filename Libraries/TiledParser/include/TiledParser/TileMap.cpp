#include "TileMap.h"
#include "Base64.h"
#include "Object.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <iostream>

namespace fs = std::filesystem;

namespace TiledParser {

	using JSON = nlohmann::json;

	TileMap::TileMap(std::string filePath)
		: m_FilePath(filePath)
	{
		std::string jsonStr = this->ReadJSONFile(filePath);

		if (!jsonStr.empty())
		{
			if (!this->Parse(jsonStr))
			{
				std::cout << "ERROR: Failed to parse file " << filePath << std::endl;
			}
		}
	}

	const float& TileMap::GetVersion() const
	{
		return this->m_Version;
	}

	const int& TileMap::GetCompressionLevel() const
	{
		return this->m_CompressionLevel;
	}

	const std::string& TileMap::GetType() const
	{
		return this->m_Type;
	}

	const std::string& TileMap::GetOrientation() const
	{
		return this->m_Orientation;
	}

	const std::string& TileMap::GetRenderOrder() const
	{
		return this->m_RenderOrder;
	}

	const int& TileMap::GetWidth() const
	{
		return this->m_Width;
	}

	const int& TileMap::GetHeight() const
	{
		return this->m_Height;
	}

	const int& TileMap::GetNextLayerId() const
	{
		return this->m_NextLayerId;
	}

	const int& TileMap::GetNextObjectId() const
	{
		return this->m_NextObjectId;
	}

	const std::string& TileMap::GetTiledVersion() const
	{
		return this->m_TiledVersion;
	}

	const int& TileMap::GetTileWidth() const
	{
		return this->m_TileWidth;
	}

	const int& TileMap::GetTileHeight() const
	{
		return this->m_TileHeight;
	}

	const std::string& TileMap::GetBackgroundColor() const
	{
		return this->m_BackgroundColor;
	}

	const std::vector<TileSet>& TileMap::GetTileSets() const
	{
		return this->m_TileSets;
	}

	const std::vector<TileLayer>& TileMap::GetTileLayers() const
	{
		return this->m_TileLayers;
	}

	const std::vector<ObjectGroup>& TileMap::GetObjectGroups() const
	{
		return this->m_ObjectGroups;
	}

	const std::string TileMap::ReadJSONFile(std::string& filePath)
	{
		std::ifstream file(filePath);

		if (file.is_open()) {
			std::string jsonStr((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			file.close();
			return jsonStr;
		}
		else {
			std::cout << "ERROR: Failed to read file " << filePath << std::endl;
			perror(filePath.c_str());
		}

		return "";
	}

	const bool TileMap::Parse(std::string& jsonStr)
	{
		auto json = JSON::parse(jsonStr);

		this->m_Version = json["version"].get<float>();
		this->m_CompressionLevel = json["compressionlevel"].get<int>();
		this->m_Type = json["type"].get<std::string>();
		this->m_Orientation = json["orientation"].get<std::string>();
		this->m_RenderOrder = json["renderorder"].get<std::string>();
		this->m_Width = json["width"].get<int>();
		this->m_Height = json["height"].get<int>();
		this->m_NextLayerId = json["nextlayerid"].get<int>();
		this->m_NextObjectId = json["nextobjectid"].get<int>();
		this->m_TiledVersion = json["tiledversion"].get<std::string>();
		this->m_TileWidth = json["tilewidth"].get<int>();
		this->m_TileHeight = json["tileheight"].get<int>();
		this->m_BackgroundColor = json.value("backgroundcolor", "#000000");

		for (const auto& jsonLayer : json["layers"])
		{
			if (jsonLayer["type"] == "tilelayer")
			{
				std::string data = jsonLayer["data"].get<std::string>();
				std::string decodedData;

				std::string errorMessage = Base64::Decode(data, decodedData);

				if (!errorMessage.empty())
				{
					std::cout << "ERROR: Failed to decode base64 attribute 'layers > data'" << std::endl;
					return false;
				}

				std::vector<int> tileIds;
				int dataSize = decodedData.size();
				int tileIndex = 0;

				while (tileIndex < dataSize)
				{
					if (decodedData[tileIndex])
					{
						tileIds.push_back((int32_t)decodedData[tileIndex]);
					}
					tileIndex += 4;
				}

				TileLayer tileLayer(
					jsonLayer["id"].get<int>(),
					jsonLayer["name"].get<std::string>(),
					jsonLayer["compression"].get<std::string>(),
					jsonLayer["encoding"].get<std::string>(),
					jsonLayer["type"].get<std::string>(),
					jsonLayer["width"].get<int>(),
					jsonLayer["height"].get<int>(),
					jsonLayer["opacity"].get<float>(),
					jsonLayer["visible"].get<bool>(),
					jsonLayer["x"].get<int>(),
					jsonLayer["y"].get<int>(),
					tileIds
				);

				this->m_TileLayers.push_back(tileLayer);
			}
			else if (jsonLayer["type"] == "objectgroup")
			{
				std::vector<Object> objects;

				for (const auto& jsonObject : jsonLayer["objects"])
				{
					std::string type("rectangle");

					std::vector<Point> polygon;

					if (jsonObject.contains("polygon"))
					{
						for (const auto& jsonPoint : jsonObject["polygon"])
						{
							Point point;
							point.x = jsonPoint["x"].get<float>();
							point.y = jsonPoint["y"].get<float>();

							polygon.push_back(point);
						}

						if (!polygon.empty())
						{
							type = "polygon";
						}
					}

					if (jsonObject.contains("point") && jsonObject["point"].get<bool>())
					{
						type = "point";
					}

					if (jsonObject.contains("ellipse") && jsonObject["ellipse"].get<bool>())
					{
						type = "ellipse";
					}

					Object object(
						jsonObject["id"].get<int>(),
						jsonObject["name"].get<std::string>(),
						type,
						jsonObject["visible"].get<bool>(),
						jsonObject["rotation"].get<int>(),
						jsonObject["width"].get<float>(),
						jsonObject["height"].get<float>(),
						jsonObject["x"].get<float>(),
						jsonObject["y"].get<float>(),
						polygon
					);

					objects.push_back(object);
				}

				ObjectGroup objectGroup(
					jsonLayer["id"].get<int>(),
					jsonLayer["name"].get<std::string>(),
					jsonLayer["type"].get<std::string>(),
					jsonLayer["opacity"].get<float>(),
					jsonLayer["visible"].get<bool>(),
					jsonLayer["x"].get<int>(),
					jsonLayer["y"].get<int>(),
					jsonLayer["draworder"].get<std::string>(),
					objects
				);

				this->m_ObjectGroups.push_back(objectGroup);
			}
		}

		fs::path filePath(this->m_FilePath);
		std::string basePath = filePath.parent_path().string() + "/";

		for (const auto& jsonTileSet : json["tilesets"])
		{
			std::string source = basePath + jsonTileSet["source"].get<std::string>();

			std::string tileSetString = this->ReadJSONFile(source);

			if (tileSetString.empty()) continue;

			auto tileSetJsonObject = JSON::parse(tileSetString);

			TileSet tileSet(
				jsonTileSet["firstgid"].get<int>(),
				jsonTileSet["source"].get<std::string>(),
				tileSetJsonObject["tiledversion"].get<std::string>(),
				tileSetJsonObject["version"].get<float>(),
				tileSetJsonObject["type"].get<std::string>(),
				tileSetJsonObject["name"].get<std::string>(),
				tileSetJsonObject["image"].get<std::string>(),
				tileSetJsonObject["imagewidth"].get<int>(),
				tileSetJsonObject["imageheight"].get<int>(),
				tileSetJsonObject["tilewidth"].get<int>(),
				tileSetJsonObject["tileheight"].get<int>(),
				tileSetJsonObject["tilecount"].get<int>(),
				tileSetJsonObject["columns"].get<int>(),
				tileSetJsonObject["margin"].get<int>(),
				tileSetJsonObject["spacing"].get<int>(),
				tileSetJsonObject["transparentcolor"].get<std::string>()
			);

			this->m_TileSets.push_back(tileSet);
		}

		return true;
	}

}
