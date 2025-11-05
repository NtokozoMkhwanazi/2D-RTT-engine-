#pragma once
#include <SFML/Graphics.hpp>

enum class PlayerState {
    Idle = 0,
    Walk,
    Jump
};

struct Transform {
    sf::Vector2f position; // entity position
    sf::Vector2f size;     // entity width and height
};


struct Physics {
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool onGround = false; // needed for jumping logic
};



struct PlayerControl {};

struct Renderable {
    sf::Sprite* sprite = nullptr;
};

struct AnimationComponent {
    int frameWidth;
    int frameHeight;
    int currentFrame = 0;
    int frameCount;
    float frameTime;
    float timer = 0.f; // to track frame time
    
    int columns;     // total columns in sprite sheet
    int rows;    

    float scaleX = 1.f;
    float scaleY = 1.f;
    int spacing = 0;
};



