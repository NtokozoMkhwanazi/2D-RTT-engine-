#pragma once
#include "ECS.h"
#include "Components.h"
#include <SFML/Graphics.hpp>
#include <vector>

class PhysicsSystem {
public:
    void update(ECSRegistry& ecs, float dt, float gravity, const std::vector<sf::RectangleShape>& platforms) {
        auto entities = ecs.getAll<Physics>();
        for (auto& [entity, phys] : entities) {
            auto* trans = ecs.getComponent<Transform>(entity);
            if (!trans) continue;

            // Apply gravity if not on ground
            if (!phys->onGround)
                phys->velocity.y += gravity * dt;

            // Update position
            trans->position += phys->velocity * dt;

            // Reset onGround
            phys->onGround = false;

            // Collision with platforms
            for (auto& plat : platforms) {
                sf::Vector2f platPos = plat.getPosition();
                sf::Vector2f platSize = plat.getSize();

                bool overlapX = trans->position.x + trans->size.x > platPos.x &&
                                trans->position.x < platPos.x + platSize.x;
                bool overlapY = trans->position.y + trans->size.y > platPos.y &&
                                trans->position.y < platPos.y + platSize.y;

                if (overlapX && overlapY) {
                    // Snap to top of platform
                    trans->position.y = platPos.y - trans->size.y;
                    phys->velocity.y = 0;
                    phys->onGround = true;
                }
            }
        }
    }
};

