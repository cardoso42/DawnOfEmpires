#ifndef HELPSTATSPAGE_HPP
#define HELPSTATSPAGE_HPP

#include "HelpPage.hpp"

class HelpStatsPage : public HelpPage
{
public:
    HelpStatsPage(sf::Vector2f windowSize);

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text msg;
};

#endif