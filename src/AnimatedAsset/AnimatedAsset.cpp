#include "AnimatedAsset.hpp"

AnimatedAsset::AnimatedAsset(std::string filename, int frameCount, sf::Vector2i spriteSize, sf::Time duration) : sf::Sprite()
{
    setAnimation(filename, frameCount, spriteSize, duration);
}


AnimatedAsset::AnimatedAsset(std::string filename, int frameCount, sf::Vector2i spriteSize) : sf::Sprite()
{
    sf::Time duration = sf::seconds(frameCount / 20.f);
    setAnimation(filename, frameCount, spriteSize, duration);
}

AnimatedAsset::AnimatedAsset(std::string filename)
{
    animator = new Animator(static_cast<sf::Sprite&>(*this));

    sf::Vector2u textureSize = (AssetManager::GetTexture(filename))->getSize();
    auto& animation = animator->CreateAnimation(filename, filename, sf::seconds(1));
    animation.AddFrames({0, 0}, static_cast<sf::Vector2i>(textureSize), 1);

    setOrigin({textureSize.x * 0.5f, textureSize.y * 0.5f});
}

void AnimatedAsset::animate(sf::Time deltaTime)
{
    animator->Update(deltaTime);
}

void AnimatedAsset::fitTo(sf::Vector2i size, float proportion)
{
    float scale{1};

    sf::Vector2f maxSizeTexture = {size.x * proportion, size.y * proportion};
    
    if (getTextureRect().width > maxSizeTexture.x)
    {
        scale = maxSizeTexture.x / getTextureRect().width;
    }

    if (getTextureRect().height > maxSizeTexture.y)
    {
        scale = std::min(scale, maxSizeTexture.y / getTextureRect().height);
    }

    setScale({scale, scale});
}

void AnimatedAsset::setAnimation(std::string filename, int frameCount, sf::Vector2i spriteSize, sf::Time duration)
{
    animator = new Animator(static_cast<sf::Sprite&>(*this));

    auto& animation = animator->CreateAnimation(filename, filename, duration, true);
    animation.AddFrames({0, 0}, spriteSize, frameCount);

    setTextureRect({0, 0, spriteSize.x, spriteSize.y});
    setOrigin({spriteSize.x * 0.5f, spriteSize.y * 0.5f});
}
