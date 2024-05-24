#include "AssetManager.hpp"

#include <assert.h>
#include <sstream>

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
    // Only allow one AssetManager to exist
    // Otherwise throw an exception
    assert(sInstance == nullptr);

    sInstance = this;
}

std::string AssetManager::GenerateAbsolutePathname(std::string const& filename)
{
    std::ostringstream oss;
    oss << BASE_PATH << "/resources/" << filename;
    return oss.str();
}

sf::Texture* AssetManager::GetTexture(std::string const& filename)
{
    auto& texMap = sInstance->m_Textures;
    std::string absoluteFilename = AssetManager::GenerateAbsolutePathname(filename);

    // See if the texture is already loaded
    auto pairFound = texMap.find(absoluteFilename);

    // If yes, return the texture
    if (pairFound != texMap.end())
    {
        return &pairFound->second;
    }
    else // Else, load the texture and return it
    {
        auto& texture = texMap[absoluteFilename];
        if (!texture.loadFromFile(absoluteFilename))
        {
            std::cout << "Unable to load texture " << absoluteFilename << std::endl;
        }
        return &texture;
    }
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& filename)
{
    auto& sBufferMap = sInstance->m_SoundBuffers;
    std::string absoluteFilename = AssetManager::GenerateAbsolutePathname(filename);

    auto pairFound = sBufferMap.find(absoluteFilename);
    if (pairFound != sBufferMap.end())
    {
        return pairFound->second;
    }
    else
    {
        // Create an element in the SoundBuffer map
        auto& sBuffer = sBufferMap[absoluteFilename];
        sBuffer.loadFromFile(absoluteFilename);
        return sBuffer;
    }
}

sf::Font& AssetManager::GetFont(std::string const& filename)
{
    auto& fontMap = sInstance->m_Fonts;
    std::string absolutFilename = AssetManager::GenerateAbsolutePathname(filename);

    auto pairFound = fontMap.find(absolutFilename);
    if (pairFound != fontMap.end())
    {
        return pairFound->second;
    }
    else
    {
        // Create an element in the Fonts map
        auto& font = fontMap[absolutFilename];
        font.loadFromFile(absolutFilename);
        return font;
    }
}
