#include "Animator.hpp"

Animator::Animator(sf::Sprite& sprite)
    : m_Sprite(sprite), m_CurrentTime(), m_CurrentAnimation(nullptr)
{
}

Animator::Animation& Animator::CreateAnimation(std::string const& name,
    std::string const& textureName, sf::Time const& duration, bool loop)
{
    if (duration == sf::seconds(0))
    {
        throw std::invalid_argument("duration can't be 0");
    }

    m_Animations.push_back(
        Animator::Animation(name, textureName, duration, loop)
    );

    // If we don't have any other animations, use that as current animation
    if (m_CurrentAnimation == nullptr)
    {
        SwitchAnimation(&m_Animations.back());
    }

    return m_Animations.back();
}

void Animator::SwitchAnimation(Animator::Animation* animation)
{
    // Change the sprite texture
    if (animation != nullptr)
    {
        m_Sprite.setTexture(*(AssetManager::GetTexture(animation->m_TextureName)));
    }

    m_CurrentAnimation = animation;
    m_CurrentTime =  sf::Time::Zero; // Reset the time
}

bool Animator::SwitchAnimation(std::string const& name)
{
    auto animation = FindAnimation(name);
    if (animation != nullptr)
    {
        SwitchAnimation(animation);
        return true;
    }

    return false;
}

Animator::Animation* Animator::FindAnimation(std::string const& name)
{
    for (auto it = m_Animations.begin(); it != m_Animations.end(); ++it)
    {
        if (it->m_Name == name)
        {
            return &*it;
        }
    }

    return nullptr;
}

std::string Animator::GetCurrentAnimationName() const
{
    if (m_CurrentAnimation != nullptr)
    {
        return m_CurrentAnimation->m_Name;
    }

    // If no animation is playing, return empty string
    return "";
}

void Animator::Update(sf::Time const& dt)
{
    // If we don't have any animations yet return
    if (m_CurrentAnimation == nullptr)
    {
        return;
    }

    m_CurrentTime += dt;

    // Get the current animation frame
    float scaledTime = (m_CurrentTime.asSeconds() / m_CurrentAnimation->m_Duration.asSeconds());
    int numFrames = m_CurrentAnimation->m_Frames.size();
    int currentFrame = static_cast<int>(scaledTime * numFrames);

    // If the animation is looping, calculate the correct frame
    if (m_CurrentAnimation->m_Looping)
    {
        currentFrame %= numFrames;
    }
    else if (currentFrame >= numFrames) // If the current frame is greater than the number of frames
    {
        currentFrame = numFrames - 1; // Show last frame
    }

    // Set the texture rectangle, depending on the frame
    sf::IntRect frame = m_CurrentAnimation->m_Frames[currentFrame];
    m_Sprite.setTextureRect(frame);
}
