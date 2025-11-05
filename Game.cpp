#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Sprite Player Demo") {
    // Load background
    if (!backgroundTexture.loadFromFile("assets/background.png"))
        std::cerr << "Failed to load background!" << std::endl;

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        (float)window.getSize().x / backgroundTexture.getSize().x,
        (float)window.getSize().y / backgroundTexture.getSize().y
    );

    // --- Create floor platform ---
    sf::RectangleShape floor(sf::Vector2f(window.getSize().x, 50.f)); // full width
    floor.setPosition(0.f, window.getSize().y - 50.f); // bottom of window
    floor.setFillColor(sf::Color::Blue);
    platforms.push_back(floor);

    // --- Initialize player on top of floor ---
    float targetHeight = 150.f; // scaled sprite height
    player.init(ecs,
                sf::Vector2f(100.f, floor.getPosition().y - targetHeight),
                "assets/player.png",
                3, 8, 0.1f, targetHeight);
}

void Game::run() {
    sf::Clock clock;

    while(window.isOpen()) {
        sf::Event event;
        bool left = false, right = false, jump = false;

        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();

        // --- Player input ---
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) left = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) right = true;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) jump = true;

        float dt = clock.restart().asSeconds();

        // --- Update player movement ---
        playerSystem.update(ecs, dt, left, right, jump);

        // --- Update physics with gravity and collisions ---
        physicsSystem.update(ecs, dt, 980.f, platforms);

        // --- Determine player state for animation ---
        PlayerState state = PlayerState::Idle;
        bool facingRight = true;

        auto physicsList = ecs.getAll<Physics>();
        if(!physicsList.empty()) {
            auto* phys = physicsList[0].second;

            if(phys->velocity.y < -1.f || phys->velocity.y > 1.f) {
                state = PlayerState::Jump;
            } else if(phys->velocity.x > 1.f) {
                state = PlayerState::Walk;
                facingRight = true;
            } else if(phys->velocity.x < -1.f) {
                state = PlayerState::Walk;
                facingRight = false;
            } else {
                state = PlayerState::Idle;
            }
        }

        // --- Update animation (with state & direction) ---
        animationSystem.update(ecs, dt, state, facingRight);

        // --- Render ---
        window.clear();
        window.draw(backgroundSprite);

        // Draw player
        player.draw(ecs, window);

        // Draw platforms
        for(auto& plat: platforms) window.draw(plat);

        window.display();
    }
}

