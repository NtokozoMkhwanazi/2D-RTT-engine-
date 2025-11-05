#pragma once
#include "ECS.h"
#include "Components.h"
#include <SFML/Graphics.hpp>
#include <cmath>
class AnimationSystem {
public:
    void update(ECSRegistry& ecs, float dt, PlayerState state, bool facingRight) {
        auto entities = ecs.getAll<AnimationComponent>();
        for (auto& [entity, anim] : entities) {
            auto* rend = ecs.getComponent<Renderable>(entity);
            auto* trans = ecs.getComponent<Transform>(entity);
            if (!rend || !rend->sprite || !trans) continue;

            // Animate frames
            if (state == PlayerState::Idle) {
                anim->currentFrame = 0;
                anim->timer = 0.f;
            } else {
                anim->timer += dt;
                if (anim->timer >= anim->frameTime) {
                    anim->timer -= anim->frameTime;
                    anim->currentFrame = (anim->currentFrame + 1) % anim->frameCount;
                }
            }

            // Determine row by state
            int row = 0;
            switch (state) {
                case PlayerState::Idle: row = 0; break;
                case PlayerState::Walk: row = 1; break;
                case PlayerState::Jump: row = 2; break;
            }

            // Compute correct texture rectangle
            int column = anim->currentFrame % anim->columns;
            sf::IntRect rect(
                column * anim->frameWidth,
                row * anim->frameHeight,
                anim->frameWidth,
                anim->frameHeight
            );

            rend->sprite->setTextureRect(rect);
            rend->sprite->setPosition(trans->position + trans->size / 2.f);

            // Flip if needed
            float scaleX = std::abs(trans->size.x / anim->frameWidth);
            float scaleY = std::abs(trans->size.y / anim->frameHeight);
            rend->sprite->setScale(facingRight ? scaleX : -scaleX, scaleY);
        }
    }
};

