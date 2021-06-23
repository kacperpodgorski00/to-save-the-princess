# pragma once


class Tile
{
public:
    Tile();
    Tile(float x, float y, float gridSizeF, sf::Texture& texture);
    virtual ~Tile();

    //Functions
    void update();
    void render(sf::RenderTarget& target);

protected:
    sf::RectangleShape shape;

private:
};


