#ifndef ANIMATEDASSET_HPP
#define ANIMATEDASSET_HPP

#include "Animator.hpp"
#include "AssetManager.hpp"

#include <SFML/Graphics.hpp>

class AnimatedAsset : public sf::Sprite
{
public:
    AnimatedAsset(std::string filename, int frameCount, sf::Vector2i spriteSize);
    AnimatedAsset(std::string filename);
    void animate(sf::Time deltaTime);
private:
    Animator* animator;
};

#endif // ANIMATEDASSET_HPP
