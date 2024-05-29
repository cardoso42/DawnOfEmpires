#include "HelpArea.hpp"

HelpArea::HelpArea(sf::Vector2f viewSize) : viewSize(viewSize), rect(viewSize),
    grassTile(viewSize.x * 0.2f, viewSize.y * 0.15f, TilePiece::TileType::GRASS), 
    forestTile(viewSize.x * 0.2f, viewSize.y * 0.3f, TilePiece::TileType::FOREST),
    mineralTile(viewSize.x * 0.2f, viewSize.y * 0.45f, TilePiece::TileType::MINE)
{
    rect.setFillColor(sf::Color::Black);
    rect.setOrigin(rect.getSize() * 0.5f);
    rect.setPosition(viewSize * 0.5f);

    sf::Text title("Rules", AssetManager::GetFont("anonymous.ttf"));
    title.setOrigin({title.getLocalBounds().width * 0.5f, title.getLocalBounds().height * 0.5f});
    title.setPosition(viewSize.x * 0.5f, viewSize.y * 0.02f);
    texts.push_back(title);
}

void HelpArea::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(rect);

    for (auto text : texts)
    {
        target.draw(text);
    }

    target.draw(grassTile);
    target.draw(forestTile);
    target.draw(mineralTile);
}

// TilePieceExample implementation

HelpArea::TilePieceExample::TilePieceExample(int x, int y, TileType type) 
    : TilePiece(x, y, 0, 0)
{
    this->type = type;
    this->setColor();
}
