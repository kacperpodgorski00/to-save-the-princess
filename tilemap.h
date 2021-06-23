#pragma once

#include "tile.h"


class TileMap
{
public:
    TileMap(float gridSize, unsigned width, unsigned height);
    virtual ~TileMap();

    //Functions
    void update();
    void render(sf::RenderTarget& target);

    void addTile(const unsigned x, const unsigned y, const unsigned z);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);

private:
    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u maxSize;
    unsigned layers;
    std::vector< std::vector< std::vector< Tile* > > > map;
    sf::Texture tileTextureSheet;

};

