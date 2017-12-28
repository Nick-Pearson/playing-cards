#include "texturemanager.h"

#include "logging.h"
#include "texture.h"
#include "paths.h"

#include <iostream>
#include <cstring>

TextureManager* gTextureManager(nullptr);

TextureManager::~TextureManager()
{
  m_LoadedTextures.empty();
}


std::shared_ptr<Texture> TextureManager::FindOrLoadTexture(const std::string& filepath)
{
  TextureManagerMap::iterator it = m_LoadedTextures.find(filepath);

  if(it != m_LoadedTextures.end())
  {
    return it->second;
  }

  Texture* newTexture = new Texture(filepath.c_str());

  if(!newTexture) return nullptr;

  std::shared_ptr<Texture> newSharedTexture = std::make_shared<Texture>(newTexture);
  m_LoadedTextures.emplace(filepath, newSharedTexture);

  std::string path;
  path.append("Loaded ");
  path.append(filepath);
  path.append("...");
  LogVerbose(path.c_str());

  return newSharedTexture;
}

glm::ivec4 TextureManager::GetTileCoords(const std::string& filename, const std::string& tilename)
{
  TextureManager_TileDefFilesMap::iterator it = m_LoadedTileDefs.find(filename);
  const TileDefinitionCollection* foundMap = nullptr;

  if(it != m_LoadedTileDefs.end())
  {
    foundMap = &it->second;
  }

  //if map is not found try to load this file
  if(foundMap == nullptr)
  {
    LoadTileDefinitionCollection(filename);
    it = m_LoadedTileDefs.find(filename);

    if(it == m_LoadedTileDefs.end()) return glm::ivec4();
    foundMap = &it->second;
  }

  //now try and find the exact coords
  TextureManager_TileDefMap::const_iterator tile_it = foundMap->map.find(tilename);

  if(tile_it == foundMap->map.end())
  {
    std::string out = "Failed to load tile ";
    out.append(tilename);
    out.append(" from ");
    out.append(filename);
    Fatal(out.c_str());

    return glm::ivec4();
  }

  glm::ivec4 rtn;
  rtn.x = tile_it->second.x;
  rtn.y = tile_it->second.y;
  rtn.z = tile_it->second.x + tile_it->second.width;
  rtn.w = tile_it->second.y + tile_it->second.height;
  return rtn;
}

void TextureManager::LoadTileDefinitionCollection(const std::string& filename)
{
  std::string path = Paths::TexturePath;
  path.append("/");
  path.append(filename);

  FILE* fp = fopen(path.c_str(), "r");

  if(fp == nullptr)
  {
    path.insert(0, "Failed to load tile definition ");
    Fatal(path.c_str());
    return;
  }

  TileDefinitionCollection collection;

  {
    char tilenamebuff[255];
    TileDefinition def;

    while(fscanf(fp, "%s\n", &tilenamebuff[0]) != EOF)
    {
      if(fscanf(fp, "%d,%d,%d,%d\n", &def.x, &def.y, &def.width, &def.height) == EOF)
      {
        Fatal("Unexpected end of file");
        break;
      }
      
      collection.map.emplace(tilenamebuff, def);
    }
  }

  m_LoadedTileDefs.emplace(filename, collection);
  fclose(fp);
}
