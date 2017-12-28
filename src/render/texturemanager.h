#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <glm.hpp>

#include <memory>
#include <map>

extern class TextureManager* gTextureManager;

class Texture;

struct TileDefinition
{
  int x;
  int y;
  int width;
  int height;
};

typedef std::map<std::string, TileDefinition> TextureManager_TileDefMap;

struct TileDefinitionCollection
{
  TextureManager_TileDefMap map;
};

typedef std::map<std::string, std::shared_ptr<Texture>> TextureManagerMap;
typedef std::map<std::string, TileDefinitionCollection> TextureManager_TileDefFilesMap;

class TextureManager
{
public:
  TextureManager() {}
  ~TextureManager();

  std::shared_ptr<Texture> FindOrLoadTexture(const std::string& filepath);

  glm::ivec4 GetTileCoords(const std::string& filename, const std::string& tilename);

private:

  void LoadTileDefinitionCollection(const std::string& filename);

private:
  TextureManagerMap m_LoadedTextures;

  TextureManager_TileDefFilesMap m_LoadedTileDefs;
};

#endif
