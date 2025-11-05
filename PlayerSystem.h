#pragma once
#include "ECS.h"
#include "Components.h"
#include <SFML/Window.hpp>

class PlayerSystem {
public:
    void update(ECSRegistry& ecs, float dt, bool left, bool right, bool jump) {
        auto entities = ecs.getAll<Physics>();
        for (auto& [entity, phys] : entities) {
            if (!phys) continue;

            auto* trans = ecs.getComponent<Transform>(entity);
            if (!trans) continue;

            // Horizontal movement
            if (left) phys->velocity.x = -200.f;
            else if (right) phys->velocity.x = 200.f;
            else phys->velocity.x = 0.f;

            // Jump
            if (jump && phys->onGround) {
                phys->velocity.y = -450.f; // jump impulse
                phys->onGround = false;
            }
        }
    }
};

