#include "Player.h"
#include <iostream>

void Player::init(ECSRegistry& ecs,
                  const sf::Vector2f& startPos,
                  const std::string& textureFile,
                  int rows, int columns,
                  float frameTime,
                  float targetHeight) 
{
    entity = ecs.createEntity();

    // Load texture
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load player texture!" << std::endl;
        return;
    }

    int texWidth = texture.getSize().x;
    int texHeight = texture.getSize().y;

    int frameWidth = texWidth / columns;
    int frameHeight = texHeight / rows;

    float scaleY = targetHeight / frameHeight;
    float scaleX = scaleY; // keep aspect ratio

    // Animation component
    AnimationComponent anim;
    anim.frameWidth = frameWidth;
    anim.frameHeight = frameHeight;
    anim.frameCount = columns;   // frames per row
    anim.columns = columns;
    anim.rows = rows;
    anim.frameTime = frameTime;
    anim.currentFrame = 0;
    anim.timer = 0.f;
    ecs.addComponent(entity, anim);

    // Transform component
    Transform trans;
    trans.position = startPos;
    trans.size = sf::Vector2f(frameWidth * scaleX, frameHeight * scaleY);
    ecs.addComponent(entity, trans);

    // Physics component
    Physics phys;
    phys.velocity = {0.f, 0.f};
    phys.onGround = false;
    ecs.addComponent(entity, phys);

    // Renderable component
    Renderable rend;
    rend.sprite = new sf::Sprite(texture);
    rend.sprite->setScale(scaleX, scaleY);
    rend.sprite->setOrigin(frameWidth / 2.f, frameHeight / 2.f); // center for flipping
    ecs.addComponent(entity, rend);
}

void Player::draw(ECSRegistry& ecs, sf::RenderWindow& window) {
    auto* rend = ecs.getComponent<Renderable>(entity);
    if (rend && rend->sprite) {
        window.draw(*rend->sprite);
    }
}

