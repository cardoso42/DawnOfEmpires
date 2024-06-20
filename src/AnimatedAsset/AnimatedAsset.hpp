#ifndef ANIMATEDASSET_HPP
#define ANIMATEDASSET_HPP

#include "Animator.hpp"
#include "AssetManager.hpp"

#include <SFML/Graphics.hpp>

class AnimatedAsset : public sf::Sprite
{
public:
    AnimatedAsset(std::string filename, int frameCount, sf::Vector2i spriteSize, sf::Time duration);
    AnimatedAsset(std::string filename, int frameCount, sf::Vector2i spriteSize);
    AnimatedAsset(std::string filename);
    void animate(sf::Time deltaTime);
    void fitTo(sf::Vector2i size, float proportion);
private:
    Animator* animator;
    void setAnimation(std::string filename, int frameCount, sf::Vector2i spriteSize, sf::Time duration);
};

#endif // ANIMATEDASSET_HPP
