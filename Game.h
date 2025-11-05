#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ECS.h"
#include "PhysicsSystem.h"
#include "PlayerSystem.h"
#include "AnimationSystem.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Player player;
    ECSRegistry ecs;

    PhysicsSystem physicsSystem;
    PlayerSystem playerSystem;
    AnimationSystem animationSystem;

    std::vector<sf::RectangleShape> platforms;
};

