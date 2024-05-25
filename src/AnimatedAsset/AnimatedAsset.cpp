#include "AnimatedAsset.hpp"

AnimatedAsset::AnimatedAsset(std::string filename, int frameCount, sf::Vector2i spriteSize) : sf::Sprite()
{
    animator = new Animator(static_cast<sf::Sprite&>(*this));

    sf::Time duration = sf::seconds(frameCount / 20.f);
    auto& animation = animator->CreateAnimation(filename, filename, duration, true);
    animation.AddFrames({0, 0}, spriteSize, frameCount);

    setTextureRect({0, 0, spriteSize.x, spriteSize.y});
    setOrigin({spriteSize.x * 0.5f, spriteSize.y * 0.5f});
}

AnimatedAsset::AnimatedAsset(std::string filename)
{
    animator = new Animator(static_cast<sf::Sprite&>(*this));

    auto& animation = animator->CreateAnimation(filename, filename, sf::seconds(1));
    animation.AddFrames(
        {0, 0}, 
        static_cast<sf::Vector2i>((AssetManager::GetTexture(filename))->getSize()), 
        1
    );
}

void AnimatedAsset::animate(sf::Time deltaTime)
{
    animator->Update(deltaTime);
}
