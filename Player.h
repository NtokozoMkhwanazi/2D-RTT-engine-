#pragma once
#include "ECS.h"
#include "Components.h"
#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
    // Initialize player with ECS, position, sprite sheet, frames, animation speed, and target height
    void init(ECSRegistry& ecs, const sf::Vector2f& startPos,
              const std::string& textureFile,
              int rows, int columns,
              float frameTime, float targetHeight);

    // Draw player using ECS
    void draw(ECSRegistry& ecs, sf::RenderWindow& window);

    unsigned int entity; // ECS entity ID

private:
    sf::Texture texture; // Player sprite sheet
};

